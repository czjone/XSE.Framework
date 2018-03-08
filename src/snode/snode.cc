#include <stdlib.h>
#include <stdio.h>
#include <core/log.h>
#include <core/netio.h>
#include <string>

int main(int c,char** argc){ 
    Xse::Network::Server svr("127.0.0.1",8080);
    svr.Start();
    return 0;
}