#include "network.h"
#include "core/thread.h"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>


using namespace Xse::Network;

static EndPort Xse::Network::MakeEndPort(const char* host,Int port){
    struct addrinfo *result;  
    int err = getaddrinfo(host, NULL, NULL, &result);  
    if(err) { Log::Write(Log::Level::ERROR,"Invalid IP address"); }
    const struct sockaddr *sa = result->ai_addr;  

    EndPort endPort;
    endPort.errorCode =  err;
    if(err) endPort.msg = "Invalid IP address";
    endPort.host = host;
    endPort.port = port;
    endPort.ipfamily = sa->sa_family == AF_INET ? IP_V4 :IP_V6;
    return endPort;
}

///////////////////////////////////////////////////////
/// Xse::Network::SocketIO 
///////////////////////////////////////////////////////
Xse::Network::SocketIO::SocketIO(){

}
Xse::Network::SocketIO::~SocketIO(){

}
void Xse::Network::SocketIO::Send(const char* ptr, Size size){
    // write(this->socketfd,ptr,size,0);
}
void Xse::Network::SocketIO::ShutDown(){
    this->Dispatch(SocketIO::EventType::ON_CLOSED,this);
    // close(this->socketfd,SHUT_RDWR);
    this->socketfd = 0;
}
///////////////////////////////////////////////////////
/// Xse::Network::Accepter 
///////////////////////////////////////////////////////

Xse::Network::Accepter ::Accepter(EndPort _endport):
endPort(_endport)
{

}

Xse::Network::Accepter ::~Accepter(){
    
}

EndPort& Xse::Network::Accepter ::GetEndPort(){
    return this->endPort;
}

///////////////////////////////////////////////////////
/// Xse::Network::TCPAccepter 
///////////////////////////////////////////////////////
Xse::Network::TCPAccepter::TCPAccepter(EndPort endport) noexcept:
Xse::Network::Accepter(endport),
serverfd(0)
{
    if(this->endPort.ipfamily == IP_V4) {
        struct sockaddr_in server_addr;
        server_addr.sin_len = sizeof(struct sockaddr_in);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(endPort.port);
        server_addr.sin_addr.s_addr = inet_addr(endPort.host.c_str());
        BZERO(&(server_addr.sin_zero),8);
        serverfd = socket(AF_INET, SOCK_STREAM, 0);
        if(serverfd == -1){ Log::Write(Log::Level::ERROR,"server socket create faile."); return; }
        int ret = bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if(ret == -1){ Log::Write(Log::Level::ERROR,"bind server socket faile."); return; }
        if (listen(serverfd, 5) == -1) { Log::Write(Log::Level::ERROR,"server listen error."); return; }
    }else if(this->endPort.ipfamily == IP_V6) {
        struct sockaddr_in server_addr;
        server_addr.sin_len = sizeof(struct sockaddr_in);
        server_addr.sin_family = AF_INET6;
        server_addr.sin_port = htons(endPort.port);
        server_addr.sin_addr.s_addr = inet_addr(endPort.host.c_str());
        BZERO(&(server_addr.sin_zero),8);
        serverfd = socket(AF_INET6, SOCK_STREAM, 0);
        if(serverfd == -1){ Log::Write(Log::Level::ERROR,"server socket create faile."); return; }
        int ret = bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if(ret == -1){ Log::Write(Log::Level::ERROR,"bind server socket faile."); return; }
        if (listen(serverfd, 5) == -1) { Log::Write(Log::Level::ERROR,"server listen error."); return; }
    }
}
Xse::Network::TCPAccepter::~TCPAccepter(void){

}

SocketIO* Xse::Network::TCPAccepter::Accept(){
    if(serverfd <=0 ){
        Log::Write(Log::Level::ERROR, "server socket bind port error.");
        this->Dispatch(ServerEvent::ON_ERROR,this);
    }else {
        socklen_t address_len;
        struct sockaddr_in client_address;
        int client_socket = accept(this->serverfd, (struct sockaddr *)&client_address, &address_len);
        SocketIO* io = new SocketIO();
        io->socketfd = client_socket;
        io->remotePort = client_address.sin_port;
        io->remoteFamily = client_address.sin_family;
        io->remoteHost = std::string(inet_ntoa(client_address.sin_addr));
        this->Dispatch(ServerEvent::ON_NEW_CONNECTED,io);
    }

}

///////////////////////////////////////////////////////
/// Xse::Network::UDPAccepter 
///////////////////////////////////////////////////////
Xse::Network::UDPAccepter::UDPAccepter(EndPort endport):
Xse::Network::Accepter(endPort)
{

}

Xse::Network::UDPAccepter::~UDPAccepter(void){

}

SocketIO* Xse::Network::UDPAccepter::Accept(){

}
///////////////////////////////////////////////////////
/// Xse::Network::Server 
///////////////////////////////////////////////////////
Xse::Network::Server::Server(const char* host,Int port,CommType type) noexcept : isRun(False)

{
    EndPort _endport = Xse::Network::MakeEndPort(host,port);
    switch(type){
        case CommType::TCP:  { accepter = new TCPAccepter(_endport); break;}
        case CommType::UDP:  { accepter = new UDPAccepter(_endport);break;}
        default: Log::Write(Log::Level::ERROR, "used not supports socket type.");
    }
}

Xse::Network::Server::Server(EndPort _endport,CommType type) noexcept:        
accepter(nullptr)
,isRun(False)
{
    switch(type){
        case CommType::TCP:  { accepter = new TCPAccepter(_endport); break;}
        case CommType::UDP:  { accepter = new UDPAccepter(_endport);break;}
        default: Log::Write(Log::Level::ERROR, "used not supports socket type.");
    }
}

Xse::Network::Server::~Server(void) noexcept{
    DELETE(accepter);
}

void Xse::Network::Server::Start() noexcept{
    if(accepter == nullptr){
        this->Dispatch(ServerEvent::ON_ERROR,this);
        return ;
    }
    {
        this->isRun = True;
        this->accepter->AddEventListener(ServerEvent::ON_NEW_CONNECTED,this);
        while (true) {
            if(this->isRun == true) {
                this->accepter->Accept();
            }else {
                // Xse::Thread::Sleep(3000); //重启要用超过3稍以上的时间，因为我们不要太快速的服务器重启动，
            }
        }
    }
}

void Xse::Network::Server::Handler(void* sender,void *data) noexcept {
    
}