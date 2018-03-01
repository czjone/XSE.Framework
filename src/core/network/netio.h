#ifndef XSE_CORE_NETIO_H
#define XSE_CORE_NETIO_H 1
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
    }
}
#endif
