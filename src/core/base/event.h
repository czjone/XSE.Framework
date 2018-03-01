#ifndef XSE_CORE_BASE_EVENT_H
#define XSE_CORE_BASE_EVENT_H 1
namespace Xse {
    
    class Dispatcher;
    
    typedef int EventType;
    
    class Event {
        
        friend class Dispatcher;
        
    public:
        
        Event();
        
        virtual ~Event();
        
    protected:
        
        virtual void Handler(void* sender,void *data) = 0;
    };
    
    class Dispatcher {
        
    public:
        
        Dispatcher();
        
        virtual ~Dispatcher();
        
        void Dispatch(EventType etype,void* data = nullptr);
        
        void AddEventListener();
        
        void RemoveEventListener();
    };
}
#endif
