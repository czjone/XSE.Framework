#include "thread.h"
#include "core/log.h"
#include <unistd.h>

void Xse::Thread::Lock(std::mutex &mutex){
    mutex.lock();
}

void Xse::Thread::UnLock(std::mutex &mutex){
    mutex.unlock();
}

void  Xse::Thread::Sleep(UInt ms){
    usleep(ms*0.001); //微秒转ms.
}
 
Xse::Thread::LockGuard::LockGuard(std::mutex &_mutex):mutex((std::mutex*)&_mutex) {
     mutex->lock();
}

Xse::Thread::LockGuard::~LockGuard() {
     mutex->unlock() ; 
}
            
Xse::Thread::Thread::Thread(ThreadHandler _handler):handle(_handler)
,npid()
{

}
            
 Xse::Thread::Thread::~Thread(){
     npid = nullptr;
 }

void Xse::Thread::Thread::Start(){
    if(pthread_create(&(this->npid), NULL, Thread::Handler, this)){
        Log::Write(Log::Level::ERROR, "create thread error!");
    }
}

void* Xse::Thread::Thread::Handler(void *data){
    Xse::Thread::Thread *thread = static_cast<Xse::Thread::Thread*>(data);
    thread->handle(thread);
    return nullptr; 
}
