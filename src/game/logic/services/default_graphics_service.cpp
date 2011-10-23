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
        { }        

        Scene *scene()
        {
            return scene_.get();
        }

    private:
        std::auto_ptr<Scene> scene_;
    };

    std::auto_ptr<GraphicsService> createGraphicsService()
    {
        return std::auto_ptr<GraphicsService>(new DefaultGraphicsService);
    }
}
