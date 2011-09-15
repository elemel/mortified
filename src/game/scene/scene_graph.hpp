#ifndef MORTIFIED_SCENE_GRAPH_HPP
#define MORTIFIED_SCENE_GRAPH_HPP

#include <memory>

namespace mortified {
    class Sprite;
    class SpriteController;

    class SceneGraph {
    public:
        virtual ~SceneGraph()
        { }

        virtual void
            addSpriteController(std::auto_ptr<SpriteController> controller) = 0;
        virtual std::auto_ptr<SpriteController>
            removeSpriteController(SpriteController *controller) = 0;

        virtual void addSprite(std::auto_ptr<Sprite> sprite) = 0;
        virtual std::auto_ptr<Sprite> removeSprite(Sprite *sprite) = 0;

        virtual void update() = 0;
        virtual void draw() = 0;
    };
}

#endif
