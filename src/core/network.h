#ifndef XSE_CORE_NETWORK_NETIO_H
#define XSE_CORE_NETWORK_NETIO_H 1

#include <core/macros.h>
#include <core/types.h>
#include <core/event.h>
#include <core/stream.h>

namespace Xse {
    namespace Network {

        #define MAX_CLIENT_CONNECT 100

        class TCPAccepter;
        class UDPAccepter;

        class SocketIO : virtual public Event::Dispatcher{
            friend class TCPAccepter;
            friend class UDPAccepter;
            public :
                enum EventType {
                    ON_RECIVE_DATA,
                    ON_ERROR,
                    ON_CLOSED,
                };
        public:
            SocketIO();
            virtual ~SocketIO();
            void Send(const char* ptr, Size size);
            void ShutDown();
        private:
            Int socketfd;
            std::string remoteHost;
            std::string remotePort;
            std::string remoteFamily;
        };

        enum CommType : unsigned char {
            TCP = 0x01,
            UDP = 0x02,
        };

        typedef unsigned char IPFamily;
        #define IP_V4 AF_INET
        #define IP_V6 AF_INET6 

        class EndPort {
        public:
            IPFamily ipfamily;
            Int port;
            std::string host;
            std::string msg;
            Int errorCode;
        };

        static EndPort MakeEndPort(const char* host,Int port);

        enum ServerEvent :Event::EventType {
            ON_NEW_CONNECTED = 0x01,
            ON_ERROR = 0x02,
        };

        class Accepter : virtual public Event::Dispatcher {
        public:
            
            Accepter(EndPort endPort);

            virtual ~Accepter();

            virtual SocketIO* Accept() = 0;

            EndPort& GetEndPort();

        protected:
            EndPort endPort;
        };

        class TCPAccepter : virtual public Accepter {
            friend class SocketIO;
            public:
                TCPAccepter(EndPort endport) noexcept;
                virtual ~TCPAccepter(void);
                virtual SocketIO* Accept();
                
            private:
                Int serverfd;
        };

        class UDPAccepter: virtual public Accepter {
            friend class SocketIO;
            public:
            UDPAccepter(EndPort endport);
            virtual ~UDPAccepter(void);
            virtual SocketIO* Accept();
        };

        class Server: virtual public Event::Dispatcher,virtual Event::Listener {
            
        public:

            Server(const char* host,Int port,CommType typ) noexcept;

            Server(EndPort endPort,CommType type) noexcept;
            
            virtual ~Server(void) noexcept;

            void Start() noexcept;

            virtual void Handler(void* sender,void *data) noexcept override;

        private:
            Accepter * accepter;
            Boolean isRun;
        };

        class Client :Event::Dispatcher {
        public:
            Client();
            virtual ~Client();
            void ConnectAsy();    
        };
    }
}
#endif
