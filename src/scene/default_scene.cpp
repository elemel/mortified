#include "default_scene.hpp"

#include "context.hpp"
#include "default_layer.hpp"
#include "layer.hpp"
#include "scene.hpp"
#include "sprite.hpp"

#include <SDL/SDL_opengl.h>

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

        SpriteIterator createSprite(int layerIndex)
        {
            while (layerIndex >= int(layers_.size())) {
                layers_.push_back(createLayer(this));
            }
            Layer *layer = &layers_[layerIndex];
            return layer->createSprite(layerIndex);
        }

        void destroySprite(SpriteIterator sprite)
        {
            int layerIndex = sprite->getLayerIndex();
            Layer *layer = &layers_[layerIndex];
            layer->destroySprite(sprite);
        }

        void draw()
        {
            for (std::size_t i = layers_.size(); i >= 1; --i) {
                std::size_t j = i - 1;
                float z = -float(j);
                glPushMatrix();
                glTranslatef(0.0f, 0.0f, z);
                layers_[j].draw();
                glPopMatrix();
            }
        }

    private:
        boost::intrusive_ptr<Context> context_;
        LayerVector layers_;
    };

    std::auto_ptr<Scene> createScene(boost::intrusive_ptr<Context> context)
    {
        return std::auto_ptr<Scene>(new DefaultScene(context));
    }
}
