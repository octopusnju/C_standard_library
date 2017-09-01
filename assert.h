/* User defined ASSERT:
 *  print the <condition> and <message> to file or screen
 *
 * Keys:
 *  1. <__VA_ARGS__> is a macro that represents the whole part in <...>, <...> can only at the end like ( a, b, ... ) not ( a, ..., b )
 *  2. # is a convert symbol, convert the symbol it connects to string format. [VERY USEFULL!!]
 *  3. ## is a conjection symbol, compose symbols before and after it to a new symbol.
 *  4. printf series functions can joint strings together to a single string, only if they are real string.
 *  5. do { } while (0) is good to handle the multi line define, the behavior is same as normal function, add ; to end.
 *
 * Author: yxzhang
 * Date: 2017-09-01
 */

#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <stdio.h>
#include <stdlib.h>

#if 0 //can be changed
#define LogError(...) LogErrorToFile( __VA_ARGS__ )
#else
#define LogError(...) LogErrorToScreen( __VA_ARGS__ )
#endif

#define ErrorFile "error.log" //can be changed

#define LogErrorToFile(...) do { \
    FILE *fp = fopen( ErrorFile, "a" ); \
    fprintf( fp, __VA_ARGS__ ); \
    fclose( fp ); \
} while (0)

#define LogErrorToScreen(...) do { \
    fprintf( stderr, __VA_ARGS__ ); \
} while (0)

#define ASSERT( condition, message ) do { \
    if ( !(condition) ) { \
        LogError( "Assertion failed: " #condition ", " message "\n" ); \
        exit( EXIT_FAILURE ); \
    } \
} while (0)

#endif /*__ASSERT_H__*/
