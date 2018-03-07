#ifndef XSE_CORE_BASE_EVENT_H
#define XSE_CORE_BASE_EVENT_H 1

#include <map>
#include <vector>
#include <mutex>

namespace Xse {
    
    namespace Event {

    class Dispatcher;
    
    typedef unsigned int EventType;
    
    class Listener {
        
        friend class Dispatcher;
        
    public:
        
        Listener() noexcept;
        
        virtual ~Listener() noexcept;

        // bool operator==(const Listener *listener) const;     
    protected:
        
        //执行器不处理执行的结果，也不处理执行过程中的任何异常
        virtual void Handler(void* sender,void *data = nullptr) noexcept;
    };
    
    class Dispatcher {
        typedef std::map<EventType,std::vector<Listener*>> Events;
    public:
        
        Dispatcher();
        
        virtual ~Dispatcher();
        
        virtual void Dispatch(EventType etype,void* data = nullptr);
        
        void AddEventListener(EventType type,Listener &listener);
        
        void RemoveEventListener(EventType type,Listener &listener);

        private:
            Events evts;
            mutable std::mutex mut;
    };
    }
}
#endif
