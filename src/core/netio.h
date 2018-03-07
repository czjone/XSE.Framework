#ifndef XSE_CORE_NETWORK_NETIO_H
#define XSE_CORE_NETWORK_NETIO_H 1

#include <core/event.h>
#include <core/stream.h>

namespace Xse {
    namespace Network :Xse::IStream<Byte>,Xse::OStream<Byte> {

        class Netio{

        public:

            Netio();

            virtual ~Netio(void);

            virtual bool IsAlive() const = 0;

            virtual void Close() = 0; 
        };

        enum CommType : unsigned char {
            TCP,
            UDP,
        };
        
        class ServerOption{
            
        public:
            
            ServerOption(std::string host,int port,CommType type);

            virtual ~ServerOption(void);
            
            inline const std::string& getHost(void) const{
                return this->host;
            }
            
            inline int getPort(void) const {
                return this->port;
            }

            inline CommType GetCommType() const {
                return this->type;
            }
        private:
            const std::string host;
            int port;
            CommType type;
        };

        class Server: virtual public Event::Dispatcher {
            
        protected:
        
            enum Event : Event::EventType {
                ON_START,
                ON_STOP,
                ON_NEWCLIENT_CONNECTED,
            };

        public:
            
            Server(std::string host,std::string port);
            
            Server(ServerOption option);

            virtual ~Server(void);

            void Run() ;

            void Pause();

            void Stop();
        };
    }
}
#endif
