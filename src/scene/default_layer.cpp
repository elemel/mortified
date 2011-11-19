#include "default_scene.hpp"

#include "context.hpp"
#include "default_sprite.hpp"
#include "layer.hpp"
#include "sprite.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultLayer : public virtual Layer {
    public:
        explicit DefaultLayer(Scene *scene) :
            scene_(scene)
        { }

        SpriteIterator createSprite(int layerIndex)
        {
            return sprites_.insert(sprites_.end(), mortified::createSprite(scene_, layerIndex));
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
        Scene *scene_;
        SpriteList sprites_;
    };
    
    std::auto_ptr<Layer> createLayer(Scene *scene)
    {
        return std::auto_ptr<Layer>(new DefaultLayer(scene));
    }
}
