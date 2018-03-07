#ifndef XSE_CORE_MACROS_H
#define XSE_CORE_MACROS_H  1

#define FREE(PTR) if(PTR!=NULL) {free(PTR);PTR = NULL;}
#define DELETE(PTR) if(PTR!=NULL) {delete(PTR);PTR = NULL;}
#define DELETE_ARRAY(PTR) if(PTR!=NULL) {delete[] (PTR);PTR = NULL;}

#endif