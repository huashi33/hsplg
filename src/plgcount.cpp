#include <thread>
#include <chrono>
#include <stdio.h>
#include "node.h"

static uint32_t plgCountCount;
static std::thread *plgCountThread;
static bool plgCountIsThreadRunning;
static FuncGet_t plgCountFuncGet;



typedef uint32_t (*GetNodeName_t)(char *name);


static void plgCountOnThread(){
    while (plgCountIsThreadRunning){
        plgCountCount++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

uint32_t open(){
    plgCountCount = 0;
    plgCountIsThreadRunning = true;
    plgCountThread = new std::thread(plgCountOnThread);


    char appName[64] = {0};
    GetNodeName_t f = (GetNodeName_t)plgCountFuncGet("getNodeName");
    uint32_t ret = f(appName);
    printf("%s open plgcount\n",appName);


    return 0;
}
uint32_t close(){
    plgCountIsThreadRunning = false;
    return 0;
}

uint32_t setFuncGet(FuncGet_t f){
    plgCountFuncGet = f;
    return 0;
}



uint32_t getCount(){
    return plgCountCount;
};