#ifndef MORTIFIED_CONTROL_SERVICE_HPP
#define MORTIFIED_CONTROL_SERVICE_HPP

#include "service.hpp"

#include <list>
#include <memory>
#include <boost/function.hpp>

namespace mortified {
    class Actor;
    class State;

    class ControlService : public virtual Service {
    public:
        typedef boost::function<void (float)> UpdateHandler;
        typedef std::list<UpdateHandler> UpdateHandlerList;
        typedef UpdateHandlerList::iterator UpdateHandlerIterator;
        
        virtual UpdateHandlerIterator
        addUpdateHandler(UpdateHandler handler) = 0;

        virtual void removeUpdateHandler(UpdateHandlerIterator handler) = 0;

        virtual std::auto_ptr<State>
        createState(char const *name, Actor *actor) = 0;
    };
}

#endif
