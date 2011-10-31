#ifndef MORTIFIED_CONTROL_SERVICE_HPP
#define MORTIFIED_CONTROL_SERVICE_HPP

#include "service.hpp"

#include <list>
#include <boost/function.hpp>

namespace mortified {
    class GameObject;
    class Scene;
    
    class ControlService : public virtual Service {
    public:
        typedef boost::function<void (float)> UpdateHandler;
        typedef std::list<UpdateHandler> UpdateHandlerList;
        typedef UpdateHandlerList::iterator UpdateHandlerIterator;
        
        virtual UpdateHandlerIterator
        addUpdateHandler(UpdateHandler handler) = 0;

        virtual void removeUpdateHandler(UpdateHandlerIterator handler) = 0;
    };
}

#endif
