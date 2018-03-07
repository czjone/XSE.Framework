#ifndef XSE_CORE_THREAD_H
#define XSE_CORE_THREAD_H 1
#include <thread>
#include <mutex>
namespace Xse {
    namespace Thread {
        static void Lock(std::mutex &mutex){
            mutex.lock();
        };
        static void UnLock(std::mutex &mutex){
            mutex.unlock();
        };

        class LockGuard{
            public:
                explicit LockGuard(std::mutex &_mutex):mutex((std::mutex*)&_mutex) { mutex->lock();};
                ~LockGuard(void) { mutex->unlock() ; } ;
            private:
                std::mutex *mutex;
        };
    }
}
#endif