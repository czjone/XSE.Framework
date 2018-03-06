#include "base64.h"
#include <stdlib.h>
#include <string>

using namespace Xse;

Base64::Base64()
{
   _base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; /*这是Base64编码使用的标准字典*/
}

std::string Base64::Encode(const char * str,size_t size) {
   std::string _encode_result;
   const char * current;
   current = str;
   while(size > 2) {
       _encode_result += _base64_table[current[0] >> 2];
       _encode_result += _base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
       _encode_result += _base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
       _encode_result += _base64_table[current[2] & 0x3f];
       
       current += 3;
       size -= 3;
   }
   if(size > 0)
   {
       _encode_result += _base64_table[current[0] >> 2];
       if(size%3 == 1) {
           _encode_result += _base64_table[(current[0] & 0x03) << 4];
           _encode_result += "==";
       } else if(size%3 == 2) {
           _encode_result += _base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
           _encode_result += _base64_table[(current[1] & 0x0f) << 2];
           _encode_result += "=";
       }
   }
   return _encode_result;
}
std::string Base64::Decode(const char *str,size_t size) {
   const char DecodeTable[] =
   {
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -1, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
       -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 62, -2, -2, -2, 63,
       52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -2, -2, -2, -2, -2, -2,
       -2,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
       15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -2, -2, -2, -2, -2,
       -2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
       41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -2, -2, -2, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
       -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2
   };
   int bin = 0,i=0;
   std::string _decode_result;
   const char *current = str;
   char ch;
   while( (ch = *current++) != '\0' && size-- > 0 )
   {
       if (ch == base64_pad) { 
           if (*current != '=' && (i % 4) == 1) {
               return NULL;
           }
           continue;
       }
       ch = DecodeTable[ch];
       if (ch < 0 ) {
           continue;
       }
       switch(i % 4)
       {
           case 0:
               bin = ch << 2;
               break;
           case 1:
               bin |= ch >> 4;
               _decode_result += bin;
               bin = ( ch & 0x0f ) << 4;
               break;
           case 2:
               bin |= ch >> 2;
               _decode_result += bin;
               bin = ( ch & 0x03 ) << 6;
               break;
           case 3:
               bin |= ch;
               _decode_result += bin;
               break;
       }
       i++;
   }
	return _decode_result;
}