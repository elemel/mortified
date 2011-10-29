#ifndef MORTIFIED_GRAPHICS_SERVICE_HPP
#define MORTIFIED_GRAPHICS_SERVICE_HPP

#include "service.hpp"

#include <list>
#include <boost/function.hpp>

namespace mortified {
    class Scene;

    class GraphicsService : public virtual Service {
    public:
        typedef boost::function<void (float)> UpdateHandler;
        typedef std::list<UpdateHandler> UpdateHandlerList;
        typedef UpdateHandlerList::iterator UpdateHandlerIterator;
        
        virtual ~GraphicsService()
        { }

        virtual Scene *scene() = 0;

        virtual UpdateHandlerIterator addUpdateHandler(UpdateHandler handler) = 0;
        virtual void removeUpdateHandler(UpdateHandlerIterator handler) = 0;
    };
}

#endif
