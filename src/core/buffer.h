#ifndef XSE_CORE_BUFFER_H
#define XSE_CORE_BUFFER_H 1

#include <core/stream.h>

#define FREE(__PTR__) free(__PTR__);__PTR__=nullptr;

#define BZERO(PTR,SIZE) memset(PTR, '\0', SIZE)

namespace Xse {
/**
 PS:连续的内存,只管读的速度，不管写入的速度,快速读取和自动成倍的扩容内存
 */
    template <typename TCHAR>
    class FastReadBuffer {

        public:
        
            FastReadBuffer ():stream() {
                
            };

            FastReadBuffer (TCHAR *ptr):stream(ptr) {
                
            };

            inline Stream<TCHAR>& operator << (T& t){
                this->stream << t;
            };

            inline Stream<TCHAR>& operator >> (T& t){
                this->stream >> t;
            };
        private:
            Stream<TCHAR> stream;
    };
}


#endif /* buffer_hpp */
