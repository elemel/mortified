#ifndef MORTIFIED_GRAPHICS_SERVICE_HPP
#define MORTIFIED_GRAPHICS_SERVICE_HPP

#include "service.hpp"

#include <list>
#include <boost/function.hpp>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Sprite;

    class GraphicsService : public virtual Service {
    public:
        typedef boost::function<void (float)> UpdateHandler;
        typedef std::list<UpdateHandler> UpdateHandlerList;
        typedef UpdateHandlerList::iterator UpdateHandlerIterator;

        typedef boost::intrusive_ptr<Sprite> SpritePtr;
        typedef std::list<SpritePtr> SpriteList;
        typedef SpriteList::iterator SpriteIterator;

        virtual boost::intrusive_ptr<Context> getContext() = 0;

        virtual UpdateHandlerIterator addUpdateHandler(UpdateHandler handler) = 0;
        virtual void removeUpdateHandler(UpdateHandlerIterator handler) = 0;

        virtual SpriteIterator addSprite(SpritePtr sprite) = 0;
        virtual void removeSprite(SpriteIterator sprite) = 0;
        
        virtual void draw() = 0;
    };
}

#endif
