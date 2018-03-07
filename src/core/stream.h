#ifndef XSE_CORE_STREAM_H
#define XSE_CORE_STREAM_H 1

#include <core/types.h>
#include <core/log.h>
#include <core/macros.h>

namespace Xse {
    
    template<typename TCHAR>
    class OStream {
    public:
        virtual ~OStream(void) { };
        inline OStream& operator << (const Byte* cstr){ 
            this->Write(cstr,strlen(cstr));
            return *this; 
        };

        inline OStream& operator << (Byte c){ 
            this->Write(&c,sizeof(c)); 
            return *this; 
        };

        inline OStream& operator << (Int val){ 
            this->Write(&val,sizeof(val));
            return *this; 
        };

        inline OStream& operator << (UInt val){ 
            this->Write(&val,sizeof(val));
            return *this; 
        };

        inline OStream& operator << (Long val){ 
            this->Write(&val,sizeof(val)); 
            return *this; 
        };

        inline OStream& operator << (ULong val){ 
            this->Write(&val,sizeof(val)); 
            return *this; 
        };

        inline OStream& operator << (Short val){ 
            this->Write(&val,sizeof(val)); 
            return *this; 
        };

        inline OStream& operator << (UShort val){ 
            this->Write(&val,sizeof(val)); 
            return *this; 
        };

        protected:

            virtual Size Write(void* ptr,Size size) = 0;
    };
    
    template<typename TCHAR>
    class IStream{
        inline IStream& operator >> (char& c){ 
            this->Read(c,sizeof(c)); 
            return *this; 
        };

        inline IStream& operator >> (int& val){ 
            this->Read(val,sizeof(val)); 
            return *this; 
        };
        inline IStream& operator >> (unsigned int& val){ 
            this->Read(val,sizeof(val)); 
            return *this; 
        };

       inline  IStream& operator >> (long& val){ 
            this->Read(val,sizeof(val)); 
            return *this; 
        };

        inline IStream& operator >> (unsigned long& val){ 
            this->Read(val,sizeof(val)); 
            return *this; 
        };

        inline IStream& operator >> (short& val){ 
            this->Read(val,sizeof(val)); 
            return *this; 
        };

        inline IStream& operator >> (unsigned short& val){ 
            this->Read(val,sizeof(val)); 
            return *this; 
        };

        protected:

            virtual Size Read(void* ptr,Size size) = 0;

        public:

            virtual Boolean Eof() const  = 0;
    };


    #define DEFAULT_CAP 8
    template<typename TCHAR>
    class StreamBase {
        public:
        explicit StreamBase()noexcept :  
        len (0),
        pos(0),
        cap(0),
        ptr(nullptr),
        isLocalPtr(True)  {
            ptr = (TCHAR*)malloc(DEFAULT_CAP);
            if(ptr != NULL) {
                len = DEFAULT_CAP;
            }
        };

        StreamBase(TCHAR* ptr,Size _cap,Size _len = 0) noexcept :  
        len (_len),
        pos(0),
        cap(_cap),
        ptr(ptr),
        isLocalPtr(False)  { }

        virtual ~StreamBase(void){
            FREE(ptr);
        };
        
        inline TCHAR *getPtr() const { return this->ptr; };

        inline Size Write(TCHAR * ptr,Size size){
            while(cap - pos < size) {
                if(this->CanRelloceX2() == True) {
                    if(this->RelloceX2()== False){
                        Log::Assert(False,"relloce memeory with x2 fail.");
                        return 0;
                    }
                }else {
                    Log::Assert(False,"buffer not allow relloc buffer size when buffer is full.");
                    return 0;
                }
            }
            auto tsize = sizeof(TCHAR);
            Size writeRet = memcpy(this->ptr + pos,ptr,tsize* size) / tsize;
            pos += writeRet;
            return writeRet;
        };

        inline Size Read(Byte * bufer,Size size) {
            Size rLen = this->len - this->pos;
            Size ret = memcpy(bufer,this->ptr,rLen* sizeof(TCHAR)) / sizeof(TCHAR);
            if(ret < rLen) {
                Log::Write(Log::Level::WARRNIGN,"parmers set size morthan read len.");
            }
            return ret;
        };

        inline Boolean Eof () const {
            return this->pos >= this->len;
        };
        
        inline Boolean ReOff(Pos_Type pos) {
            if(pos>= this->cap) {
                Log::Write(Log::Level::ERROR,"set pos morthan the buffer cap.");
                return False;
            } 
            this -> pos = pos;
        }
        
        inline void SetCanRelloc(Boolean b) {
            this->canRelloc = true;
        }
    protected:

        /** 是否可成倍的增加内存 ***/
        virtual Boolean CanRelloceX2() { return canRelloc == True || this->isLocalPtr; };
        virtual Boolean RelloceX2() {
            if(this->CanRelloceX2() == False) {
                Log::Assert(False,"can Relloc x2 with not local ptr.");
                return False;
            } 
            TCHAR* rawPtr = this->ptr;
            this->ptr = (TCHAR*)malloc(this->cap * 2);
            if(this->ptr == NULL) {
                this->ptr = rawPtr;
                Log::Assert(False,"relloc buffer error!");
            }else {
                Size rawLen = this->len*sizeof(TCHAR);
                this->cap = rawLen;
                if(memcpy(this->ptr,rawPtr,rawLen) == rawLen){
                    FREE(rawPtr);
                    return True;
                }else {
                    FREE(this->ptr);
                    this->ptr = rawPtr;
                    Xse::Log::Assert(False,"Relloc buffer is success.but copy data is fail.");
                    return True;
                }
            }
         };

    private:
        Size len;
        Size pos;
        Size cap;
        TCHAR* ptr;
        Boolean isLocalPtr;
        Boolean canRelloc;
    };

    template<typename TCHAR>
    class Stream : IStream<TCHAR>,OStream<TCHAR>{

        typedef StreamBase<TCHAR> Buffer;

    protected:
        virtual Size Write(void* ptr,Size size) {
            return this->buf.Write(ptr,size * sizeof(TCHAR));
        } ;

        virtual Size Read(void* ptr,Size size) {
            return this->buf.read(ptr,size * sizeof(TCHAR));
        };

    public:
        
        Stream():buf(){
            
        };

        Stream(TCHAR* ptr,Size _cap,Size _len = 0):buf(ptr,_cap,_len){
            
        };
        
        virtual ~Stream(){ };
        
        virtual Boolean Eof() const {
            return this->buf.Eof();
        };

        template<typename WType>
        inline Stream& operator << (WType val){
            return this->Write(val);
        };

        template<typename WType>
        inline Stream& operator >> (WType& val){
            return this->Read(val);
        };
    private:
        Buffer buf;
    };
}

#endif