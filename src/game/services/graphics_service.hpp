#ifndef MORTIFIED_GRAPHICS_SERVICE_HPP
#define MORTIFIED_GRAPHICS_SERVICE_HPP

#include "service.hpp"

#include <list>
#include <boost/function.hpp>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Scene;

    class GraphicsService : public virtual Service {
    public:
        typedef boost::function<void (float)> UpdateHandler;
        typedef std::list<UpdateHandler> UpdateHandlerList;
        typedef UpdateHandlerList::iterator UpdateHandlerIterator;

        virtual boost::intrusive_ptr<Context> context() = 0;
        virtual void context(boost::intrusive_ptr<Context> context) = 0;

        virtual Scene *scene() = 0;

        virtual UpdateHandlerIterator addUpdateHandler(UpdateHandler handler) = 0;
        virtual void removeUpdateHandler(UpdateHandlerIterator handler) = 0;
    };
}

#endif
