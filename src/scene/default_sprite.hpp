#ifndef MORTIFIED_DEFAULT_SPRITE_HPP
#define MORTIFIED_DEFAULT_SPRITE_HPP

#include <memory>

namespace mortified {
    class Sprite;
    class Scene;

    std::auto_ptr<Sprite> createSprite(Scene *scene);
}

#endif
