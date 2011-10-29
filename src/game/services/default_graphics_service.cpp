#include "default_graphics_service.hpp"

#include "default_scene.hpp"
#include "graphics_service.hpp"
#include "scene.hpp"

namespace mortified {
    class DefaultGraphicsService : public virtual GraphicsService {
    public:
        DefaultGraphicsService() :
            scene_(createScene())
        { }        

        void update(float dt)
        {
            for (UpdateHandlerIterator i = handlers_.begin();
                 i != handlers_.end(); ++i)
            {
                (*i)(dt);
            }
        }

        Scene *scene()
        {
            return scene_.get();
        }

        UpdateHandlerIterator addUpdateHandler(UpdateHandler handler)
        {
            return handlers_.insert(handlers_.end(), handler);
        }

        void removeUpdateHandler(UpdateHandlerIterator handler)
        {
            handlers_.erase(handler);
        }

    private:
        std::auto_ptr<Scene> scene_;
        UpdateHandlerList handlers_;
    };

    std::auto_ptr<GraphicsService> createGraphicsService()
    {
        return std::auto_ptr<GraphicsService>(new DefaultGraphicsService);
    }
}
