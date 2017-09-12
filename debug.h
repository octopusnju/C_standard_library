/* User defined DEBUG:
 *  print messages to screen
 *
 * Keys:
 *  1. <__VA_ARGS__> is a macro that represents the whole part in <...>, <...> can only at the end like ( a, b, ... ) not ( a, ..., b )
 *  2. __FILE__ is a real string, __func__ is a string pointer (const char *)
 *  3. printf type function can compose several real strings together
 *  4. add ## before <__VA_ARGS__> can handle the situation that the length of <...> is 0
 *  5. 5-level log types: verbose < debug < info < warn < error
 *
 * Author: yxzhang
 * Date: 2017-09-01
 * Date: 2017-09-12
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define __VERBOSE__ 1
#define __DEBUG__   1
#define __INFO__    1
#define __WARN__    1
#define __ERROR__   1

#define LOG( name, fmt, ...) do { \
    printf( "[%s][" __FILE__ "] %s:%04d | " fmt "\n", name, __func__, __LINE__, ##__VA_ARGS__ ); \
} while (0)

#if __VERBOSE__ 
#define VERBOSE( fmt, ... ) LOG( "VERB", fmt, ##__VA_ARGS__)
#else
#define VERBOSE( ... )
#endif

#if __DEBUG__ 
#define DEBUG( fmt, ... ) LOG( "DBUG", fmt, ##__VA_ARGS__)
#else
#define DEBUG( ... )
#endif

#if __INFO__ 
#define INFO( fmt, ... ) LOG( "INFO", fmt, ##__VA_ARGS__)
#else
#define INFO( ... )
#endif

#if __WARN__ 
#define WARN( fmt, ... ) LOG( "WARN", fmt, ##__VA_ARGS__)
#else
#define WARN( ... )
#endif

#if __ERROR__ 
#define ERROR( fmt, ... ) LOG( "ERRO", fmt, ##__VA_ARGS__)
#else
#define ERROR( ... )
#endif

#endif /*__DEBUG_H__*/
