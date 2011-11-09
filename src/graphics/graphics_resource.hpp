#ifndef MORTIFIED_GRAPHICS_RESOURCE_HPP
#define MORTIFIED_GRAPHICS_RESOURCE_HPP

#include "ref_counted.hpp"

#include <list>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Framebuffer;
    class Texture;

    class GraphicsResource : public virtual RefCounted {
    public:
        typedef std::list<GraphicsResource *> ChildList;
        typedef std::list<GraphicsResource *>::iterator ChildIterator;
        typedef std::pair<ChildIterator, ChildIterator> ChildRange;
        typedef boost::intrusive_ptr<GraphicsResource> ParentPtr;
        typedef std::pair<ParentPtr, ChildIterator> ParentPair;
        typedef std::list<ParentPair> ParentList;
        typedef std::list<ParentPair>::iterator ParentIterator;
        typedef std::pair<ParentIterator, ParentIterator> ParentRange;
        
        virtual ~GraphicsResource()
        { }

        virtual bool exists() const = 0;

        virtual void create() = 0;
        virtual void destroy() = 0;
        virtual void invalidate() = 0;

        virtual Context *asContext() = 0;
        virtual Context const *asContext() const = 0;

        virtual Framebuffer *asFramebuffer() = 0;
        virtual Framebuffer const *asFramebuffer() const = 0;

        virtual Texture *asTexture() = 0;
        virtual Texture const *asTexture() const = 0;

        virtual ParentRange getParents() = 0;
        virtual ChildRange getChildren() = 0;

        virtual ChildIterator addChild(GraphicsResource *child) = 0;
        virtual void removeChild(ChildIterator child) = 0;
    };
}

#endif
