#ifndef MORTIFIED_RENDER_SERVICE_HPP
#define MORTIFIED_RENDER_SERVICE_HPP

#include "service.hpp"

#include <list>
#include <boost/function.hpp>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Scene;
    class Sprite;

    class RenderService : public virtual Service {
    public:
        typedef boost::function<void (float)> UpdateHandler;
        typedef std::list<UpdateHandler> UpdateHandlerList;
        typedef UpdateHandlerList::iterator UpdateHandlerIterator;

        virtual UpdateHandlerIterator addUpdateHandler(UpdateHandler handler) = 0;
        virtual void removeUpdateHandler(UpdateHandlerIterator handler) = 0;

        virtual Scene *getScene() = 0;
        virtual Scene const *getScene() const = 0;
        
        virtual void draw() = 0;
    };
}

#endif
