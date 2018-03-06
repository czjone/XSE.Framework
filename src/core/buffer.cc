#include "buffer.h"
using namespace Xse;
FastReadBuffer::FastReadBuffer():
ptr(nullptr),
pos(0),
cap(DEFAULT_CAP),
len(0){
    ptr = (char*)malloc(DEFAULT_CAP);
    BZERO(ptr, DEFAULT_CAP);
};

FastReadBuffer::FastReadBuffer(const char* c,size_t _len){
    pos = 0;
    cap = len = _len;
    ptr = (char*)malloc(cap);
    memcpy(ptr, c, _len);
}

FastReadBuffer::~FastReadBuffer(void){
    FREE(this->ptr);
    this->pos = 0;
    this->cap = 0;
    this->len = 0;
}