#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define __INFO__
#define __WARN__
#define __ERROR__

#ifdef __INFO__
#define INFO(format,...) printf("FILE: "__FILE__", LINE: %04d, INFO: "format"\n", __LINE__, ##__VA_ARGS__)
#else
#define INFO(format,...)
#endif

#ifdef __WARN__
#define WARN(format,...) printf("FILE: "__FILE__", LINE: %04d, WARN: "format"\n", __LINE__, ##__VA_ARGS__)
#else
#define WARN(format,...)
#endif

#ifdef __ERROR__
#define ERROR(format,...) printf("FILE: "__FILE__", LINE: %04d, ERROR: "format"\n", __LINE__, ##__VA_ARGS__)
#else
#define ERROR(format,...)
#endif

#endif /*__DEBUG_H__*/
