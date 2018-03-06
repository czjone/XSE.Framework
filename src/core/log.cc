#include "log.h"
#include <stdlib.h>
#include <stdio.h>

void Xse::Log::Write(Level level,const char* msg){
    printf("%s",msg);
}

void Xse::Log::Write(Level level,std::string &msg){
    printf("%s",msg.c_str());
}

void Xse::Log::Assert(bool exp,const char* msg){
    if(exp != true) {
        Xse::Log::Write(Level::FAIL,msg);
    }
}