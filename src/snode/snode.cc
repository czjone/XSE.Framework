#include <stdlib.h>
#include <stdio.h>
#include <core/log.h>
#include <core/network.h>
#include <string>

int main(int c,char** argc){ 
    Xse::Network::Server svr("127.0.0.1",8080,Xse::Network::CommType::TCP);
    svr.Start();
    return 0;
}