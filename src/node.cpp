#include <stdio.h>
#include <stdint.h>
#include <map>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>
#include "node.h"

#define APPNAME "TestNode"

static std::map<std::string,void*> mapFuncs;


static uint32_t nodeGetNodeName(char *name){
    snprintf(name,64,APPNAME);
    return 0;
}

static void* nodeFuncGet(const char *name){
    auto it = mapFuncs.find(name);
    if(mapFuncs.end() == it){
        return nullptr;
    }

    return it->second;
}



//node_name + plugin_name + func_name
int main(int argc,char **argv){
    printf("hello world\n");

    //init funcs
    mapFuncs["getNodeName"] = (void *)nodeGetNodeName;


    //load plg
    const char* plgName = argv[1];
    HMODULE handle = LoadLibrary(plgName);
    open_t plgOpen = (open_t)GetProcAddress(handle, "open");
    close_t plgClose = (close_t)GetProcAddress(handle, "close");
    setFuncGet_t plgSetFuncGet = (setFuncGet_t)GetProcAddress(handle, "setFuncGet");
    

    
    uint32_t funcNum = argc - 2;
    for (uint32_t i = 0; i < funcNum; i++){
        const char* funcName = argv[2 + i];
        void *func =  (void *)GetProcAddress(handle, funcName);
        mapFuncs[funcName] = func;
    }

    plgSetFuncGet(nodeFuncGet);
    plgOpen();

    for (auto &i : mapFuncs){
        printf("%s:%p\n",i.first.c_str(),i.second);
    }
    
    

    //heart
    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(5));
        printf("i am alive\n");
    }
    
    plgClose();
    return 0;
}