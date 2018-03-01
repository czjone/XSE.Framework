#ifndef XSE_CORE_NETWORK_NETIO_H
#define XSE_CORE_NETWORK_NETIO_H 1

#include "core/base/event.h"
#include <string>


namespace Xse {
    namespace Network {
        class Netio {
            
            typedef void (*)(char* bytes,size_t size) OnReadComplate;

        public:

            Netio();

            virtual ~Netio(void);

            virtual void Write(char* byte,size_t size);

            virtual void WriteAsy(char* bytes,size_t size);

            virtual size_t Read(char* buf,size_t size);

            virtual size_t ReadAsy(size *size,OnReadComplate callback);

            virtual bool IsAlive() const;

            virtual void Close();
        };
        
        class ServerOption{
            
        public:
            
            ServerOption(std::string host,int port);
            
            inline std::string& getHost(void) const{
                return this->host;
            }
            
            inline int getPort(void) const {
                return this->port;
            }
        private:
            std::string host;
            int port;
        }
        class Server:Dispatcher {
            
        public:
            
            Server(string host,string port);
            
            Server(ServerOption option);
            
        }
    }
}
#endif
