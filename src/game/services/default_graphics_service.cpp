#include "default_graphics_service.hpp"

#include "context.hpp"
#include "default_scene.hpp"
#include "graphics_service.hpp"
#include "scene.hpp"

namespace mortified {
    class DefaultGraphicsService : public virtual GraphicsService {
    public:
        DefaultGraphicsService() :
            scene_(createScene())
        { }

        void load(rapidxml::xml_node<> *node)
        { }
        
        void save(rapidxml::xml_node<> *parent)
        { }

        void update(float dt)
        {
            for (UpdateHandlerIterator i = handlers_.begin();
                 i != handlers_.end(); ++i)
            {
                (*i)(dt);
            }
        }

        boost::intrusive_ptr<Context> context()
        {
            return context_;
        }

        void context(boost::intrusive_ptr<Context> context)
        {
            context_ = context;
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
        boost::intrusive_ptr<Context> context_;
        std::auto_ptr<Scene> scene_;
        UpdateHandlerList handlers_;
    };

    std::auto_ptr<GraphicsService> createGraphicsService()
    {
        return std::auto_ptr<GraphicsService>(new DefaultGraphicsService);
    }
}
