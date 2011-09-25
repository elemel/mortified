#include "default_graphics_manager.hpp"

#include "graphics_manager.hpp"
#include "graphics_resource.hpp"

namespace mortified {
    class DefaultGraphicsManager : public virtual GraphicsManager {
    public:
        ResourceRange resources()
        {
            return ResourceRange(resources_.begin(), resources_.end());
        }

        ConstResourceRange resources() const
        {
            return ConstResourceRange(resources_.begin(), resources_.end());
        }

        ResourceIterator addResource(ResourcePtr resource)
        {
            return resources_.insert(resources_.end(), resource);
        }

        ResourcePtr removeResource(ResourceIterator resource)
        {
            ResourcePtr result = *resource;
            resources_.erase(resource);
            return result;
        }

        void create()
        {
            for (ResourceIterator i = resources_.begin();
                 i != resources_.end(); ++i)
            {
                (*i)->create();
            }
        }

        void destroy()
        {
            for (ResourceIterator i = resources_.begin();
                 i != resources_.end(); ++i)
            {
                (*i)->destroy();
            }
        }

        void invalidate()
        {
            for (ResourceIterator i = resources_.begin();
                 i != resources_.end(); ++i)
            {
                (*i)->invalidate();
            }
        }

    private:
        ResourceList resources_;
    };

    boost::shared_ptr<GraphicsManager> createGraphicsManager()
    {
        return boost::shared_ptr<GraphicsManager>(new DefaultGraphicsManager);
    }
}
