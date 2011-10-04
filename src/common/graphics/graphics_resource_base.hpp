#ifndef MORTIFIED_GRAPHICS_RESOURCE_BASE_HPP
#define MORTIFIED_GRAPHICS_RESOURCE_BASE_HPP

#include "graphics_resource.hpp"

namespace mortified {
    class GraphicsResourceBase : public virtual GraphicsResource {
    public:
        GraphicsResourceBase() :
            refCount_(0)
        { }

        ~GraphicsResourceBase()
        {
            while (!parents_.empty()) {
                parents_.back().first->removeChild(parents_.back().second);
                parents_.pop_back();
            }
        }

        bool exists() const
        {
            return false;
        }
        
        void create()
        {
            if (!exists()) {
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
            if (exists()) {
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
            if (exists()) {
                invalidateImpl();

                for (ChildIterator i = children_.begin(); i != children_.end();
                     ++i)
                {
                    (*i)->invalidate();
                }
            }
        }
        
        void addRef() const
        {
            ++refCount_;
        }

        void release() const
        {
            if (--refCount_ <= 0) {
                delete this;
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
        
        Texture *asTexture()
        {
            return 0;
        }

        Texture const *asTexture() const
        {
            return 0;
        }

        ParentRange parents()
        {
            return ParentRange(parents_.begin(), parents_.end());
        }

        ChildRange children()
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
        mutable int refCount_;
        ParentList parents_;
        ChildList children_;

        ParentIterator addParent(GraphicsResource *parent)
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