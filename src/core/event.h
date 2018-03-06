#ifndef XSE_CORE_BASE_EVENT_H
#define XSE_CORE_BASE_EVENT_H 1

#include <map>
#include <vector>
#include <mutex>

namespace Xse {
    
    namespace Event {

    class Dispatcher;
    
    typedef int EventType;
    
    class Listener {
        
        friend class Dispatcher;
        
    public:
        
        Listener();
        
        virtual ~Listener();

        // bool operator==(const Listener *listener) const;     
    protected:
        
        virtual void Handler(void* sender,void *data) = 0;
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
