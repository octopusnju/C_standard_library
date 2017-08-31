#ifndef __FUNCTION_STATUS_H__
#define __FUNCTION_STATUS_H__

//the only api is FunctionStatus()
#define FunctionStatus()    function_status(__func__)

#define FILE_STR            "function_status.log"

void function_status(const char *func);

#endif /*__FUNCTION_STATUS_H__*/
