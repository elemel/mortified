#ifndef MORTIFIED_GRAPHICS_RESOURCE_BASE_HPP
#define MORTIFIED_GRAPHICS_RESOURCE_BASE_HPP

#include "graphics_resource.hpp"
#include "ref_counted_base.hpp"

namespace mortified {
    class GraphicsResourceBase :
        public virtual GraphicsResource,
        protected virtual RefCountedBase
    {
    public:
        ~GraphicsResourceBase()
        {
            while (!parents_.empty()) {
                parents_.back().first->removeChild(parents_.back().second);
                parents_.pop_back();
            }
        }

        bool isValid() const
        {
            return false;
        }
        
        void create()
        {
            if (!isValid()) {
                for (ParentIterator i = parents_.begin(); i != parents_.end();
                     ++i)
                {
                    i->first->create();
                }

                createImpl();
            }
        }

        void destroy()
        {
            if (isValid()) {
                for (ChildIterator i = children_.begin(); i != children_.end();
                     ++i)
                {
                    (*i)->destroy();
                }

                destroyImpl();
            }
        }
        
        void invalidate()
        {
            if (isValid()) {
                invalidateImpl();

                for (ChildIterator i = children_.begin(); i != children_.end();
                     ++i)
                {
                    (*i)->invalidate();
                }
            }
        }
        
        Context *asContext()
        {
            return 0;
        }

        Context const *asContext() const
        {
            return 0;
        }

        FrameBuffer *asFrameBuffer()
        {
            return 0;
        }
        
        FrameBuffer const *asFrameBuffer() const
        {
            return 0;
        }

        Texture *asTexture()
        {
            return 0;
        }

        Texture const *asTexture() const
        {
            return 0;
        }

        VertexBuffer *asVertexBuffer()
        {
            return 0;
        }

        VertexBuffer const *asVertexBuffer() const
        {
            return 0;
        }

        ParentRange getParents()
        {
            return ParentRange(parents_.begin(), parents_.end());
        }

        ChildRange getChildren()
        {
            return ChildRange(children_.begin(), children_.end());
        }

        ChildIterator addChild(GraphicsResource *child)
        {
            return children_.insert(children_.end(), child);
        }
        
        void removeChild(ChildIterator child)
        {
            children_.erase(child);
        }

    protected:
        ParentList parents_;
        ChildList children_;

        ParentIterator addParent(boost::intrusive_ptr<GraphicsResource> parent)
        {
            ParentIterator iterator =
                parents_.insert(parents_.end(), ParentPair());
            iterator->first = parent;
            try {
                iterator->second = parent->addChild(this);
            } catch (...) {
                parents_.pop_back();
                throw;
            }
            return iterator;
        }

        void removeParent(ParentIterator parent)
        {
            parents_.erase(parent);
        }

        virtual void createImpl()
        { }

        virtual void destroyImpl()
        { }

        virtual void invalidateImpl()
        { }
    };
}

#endif