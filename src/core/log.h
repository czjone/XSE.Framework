#ifndef XSE_CORE_LOG_H
#define XSE_CORE_LOG_H 1

#include <string>
#include <core/types.h>

namespace Xse {
    class Log {    
        public:    
        enum Level : unsigned char{
            FAIL,
            ERROR,
            WARRNIGN,
            BLLMSG,
        };

        static void Write(Level level,const char* msg);

        static void Write(Level level,std::string &msg);

        static void Assert(Boolean exp,const char* msg);
    };
}
#endif