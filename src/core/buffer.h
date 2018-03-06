#ifndef XSE_CORE_BUFFER_H
#define XSE_CORE_BUFFER_H 1

#include <string>

#define FREE(__PTR__) free(__PTR__);__PTR__=nullptr;

#define BZERO(PTR,SIZE) memset(PTR, '\0', SIZE)

namespace Xse {
/**
 PS:连续的内存,只管读的速度，不管写入的速度
 */
class buffer {
#define DEFAULT_CAP 8
public:
    buffer();
    buffer(const char* c,size_t len);
    virtual ~buffer(void);
    
    inline buffer& operator<< (const char* bytes){
        size_t len = strlen(bytes);
        return this->write(bytes, len);
    };
    
    inline buffer& write (const char* bytes,size_t len){
        size_t resizeCap = this->cap;
        while (resizeCap - this->pos < len) { resizeCap *=2; }
        if(this->cap != resizeCap){
            this->cap = resizeCap;
            char* newPtr = (char*)malloc(resizeCap);
            BZERO(newPtr, resizeCap);
            memcpy(newPtr, this->ptr, this->len);
            FREE(this->ptr);
            this->ptr = newPtr;
        }
        memcpy(this->ptr + pos, bytes, len);
        this->len += len;
        this->pos += len;
        return *this;
    };
    
    inline size_t getLen() const {
        return this->len;
    };
    
    inline size_t getCap() const {
        return this->cap;
    };
    
    inline size_t getPos() const {
        return this->pos;
    };
    
    inline const char* getPtr() const {
        return (const char*)this->ptr;
    };
    
    inline void rePos(int pos = 0) {
        this->pos = pos;
    };
    
    inline char* operator[](size_t pos){
        return this->ptr + pos;
    };
    
    inline void empty() {
        delete ptr;
        this->ptr = (char*)malloc(DEFAULT_CAP);
        this->pos = 0;
        this->len = 0;
        this->cap = DEFAULT_CAP;
    };
private:
    char* ptr;
    size_t pos;
    size_t cap;
    size_t len;
};

}


#endif /* buffer_hpp */
