#ifndef NODE_H
#define NODE_H

#include <stdint.h>

extern "C"{

typedef uint32_t(*open_t)();
typedef uint32_t(*close_t)();
typedef void*(*FuncGet_t)(const char *funcName);
typedef uint32_t(*setFuncGet_t)(FuncGet_t f);



uint32_t open();
uint32_t close();
uint32_t setFuncGet(FuncGet_t f);

}
#endif