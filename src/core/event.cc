#include "event.h"

using namespace Xse::Event;

Listener:: Listener()
{

}

Listener::~Listener(){

}

void Listener::Handler(void* sender,void *data){

}

// bool Listener::operator==(const Listener *listener) const{
//     return false; 
// }
    
Dispatcher:: Dispatcher():evts(){
    
}
        
Dispatcher::~Dispatcher(){

}
        
void Dispatcher::Dispatch(EventType etype,void* data){
    if(evts.find(etype) == evts.end()) {
        return ;
    }
    mut.lock();
    std::vector<Listener*> vects;
    vects = evts[etype];
    mut.unlock();
    auto itr = vects.begin();
    while(itr == vects.end()){
        (*itr)->Handler(this,data);
        itr++;
    }
}
        
void Dispatcher::AddEventListener(EventType type,Listener &listener){
    mut.lock();
    std::vector<Listener*> listeners;
    if(evts.find(type) == evts.end()){
        evts[type] = listeners;
    }else {
        listeners = evts[type];
    }
    listeners.push_back(&listener);
    mut.unlock();
}
        
void Dispatcher::RemoveEventListener(EventType type,Listener &listener){
    mut.lock();
    if(evts.find(type) != evts.end()){
        std::vector<Listener*> listeners = evts[type];
        for ( std::vector<Listener*>::iterator iter = listeners.begin(); iter != listeners.end();)
        {
            if(*iter == &listener) iter = listeners.erase(iter);
            else iter ++;
        }
        
        if( listeners.size() == 0) {
            evts.erase(evts.find(type));
        }
    }
    mut.unlock();
}