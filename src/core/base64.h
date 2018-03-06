#ifndef XSE_CORE_BASE64_H
#define XSE_CORE_BASE64_H 1
#include <string>
using namespace std;
namespace Xse {
    class Base64{
    private:
        std::string _base64_table;
        static const char base64_pad = '=';
    public:
        Base64();
        std::string Encode(const char * str,size_t size);
        std::string Decode(const char *str,size_t size);
    };
}

#endif
