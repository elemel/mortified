#include "default_scene.hpp"

#include "context.hpp"
#include "default_sprite.hpp"
#include "scene.hpp"
#include "sprite.hpp"

namespace mortified {
    class DefaultScene : public virtual Scene {
    public:
        explicit DefaultScene(boost::intrusive_ptr<Context> context) :
            context_(context)
        { }

        boost::intrusive_ptr<Context> getContext()
        {
            return context_;
        }

        SpriteIterator createSprite()
        {
            return sprites_.insert(sprites_.end(), mortified::createSprite(this));
        }

        void destroySprite(SpriteIterator sprite)
        {
            sprites_.erase(sprite);
        }

        void draw()
        {
            for (SpriteIterator i = sprites_.begin(); i != sprites_.end(); ++i)
            {
                i->draw();
            }
        }

    private:
        boost::intrusive_ptr<Context> context_;
        SpriteList sprites_;
    };

    std::auto_ptr<Scene> createScene(boost::intrusive_ptr<Context> context)
    {
        return std::auto_ptr<Scene>(new DefaultScene(context));
    }
}
