#ifndef MORTIFIED_GRAPHICS_RESOURCE_HPP
#define MORTIFIED_GRAPHICS_RESOURCE_HPP

#include <list>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Framebuffer;
    class Texture;

    class GraphicsResource {
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

        /// Does the resource exist in the graphics context?
        virtual bool exists() const = 0;

        /// Create the resource in the graphics context.
        virtual void create() = 0;

        /// Destroy the resource in the graphics context.
        virtual void destroy() = 0;

        /// Called when the graphics context has been lost.
        virtual void invalidate() = 0;

        virtual void addRef() const = 0;
        virtual void release() const = 0;

        virtual Context *asContext() = 0;
        virtual Context const *asContext() const = 0;

        virtual Framebuffer *asFramebuffer() = 0;
        virtual Framebuffer const *asFramebuffer() const = 0;

        virtual Texture *asTexture() = 0;
        virtual Texture const *asTexture() const = 0;

        virtual ParentRange parents() = 0;
        virtual ChildRange children() = 0;

        virtual ChildIterator addChild(GraphicsResource *child) = 0;
        virtual void removeChild(ChildIterator child) = 0;
    };

    inline void intrusive_ptr_add_ref(GraphicsResource const *resource)
    {
        resource->addRef();
    }

    inline void intrusive_ptr_release(GraphicsResource const *resource)
    {
        resource->release();
    }
}

#endif
