/* User defined DEBUG:
 *  print messages to screen
 *
 * Keys:
 *  1. <__VA_ARGS__> is a macro that represents the whole part in <...>, <...> can only at the end like ( a, b, ... ) not ( a, ..., b )
 *  2. __FILE__ is a real string, __func__ is a string pointer (const char *)
 *
 * Author: yxzhang
 * Date: 2017-09-01
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define __INFO__    1
#define __WARN__    1
#define __ERROR__   1

#if __INFO__
#define INFO( ... ) do { \
    printf( "FILE:" __FILE__ ", FUNC:%s, LINE:%04d, INFO:", __func__, __LINE__ ); \
    printf( __VA_ARGS__ ); \
} while (0)
#else
#define INFO( ... )
#endif

#if __WARN__
#define WARN( ... ) do { \
    printf( "FILE:" __FILE__ ", FUNC:%s, LINE:%04d, WARN:", __func__, __LINE__ ); \
    printf( __VA_ARGS__ ); \
} while (0)
#else
#define WARN( ... )
#endif

#if __ERROR__
#define ERROR( ... ) do { \
    printf( "FILE:" __FILE__ ", FUNC:%s, LINE:%04d, ERROR:", __func__, __LINE__ ); \
    printf( __VA_ARGS__ ); \
} while (0)
#else
#define ERROR( ... )
#endif

#endif /*__DEBUG_H__*/
