#ifndef XSE_CORE_THREAD_H
#define XSE_CORE_THREAD_H 1
#include <thread>
#include <mutex>
#include <functional>
#include <core/types.h>
#include <core/event.h>
namespace Xse {
    namespace Thread {
        
        static void Lock(std::mutex &mutex);

        static void UnLock(std::mutex &mutex);

        static void Sleep(UInt ms);

        class LockGuard{
            public:
                explicit LockGuard(std::mutex &_mutex);
                virtual ~LockGuard(void) ;
            private:
                std::mutex *mutex;
        };
        class Thread;

        typedef std::function<void(const Thread*)> ThreadHandler;

        class Thread : virtual public Event::Dispatcher {

        public:
            Thread(ThreadHandler handler);
            
            virtual ~Thread();

            void Start();

        private:
            static void* Handler(void* data);

        private:

            Xse::Thread::ThreadHandler handle;

            pthread_t npid;;
        };
    }
}
#endif