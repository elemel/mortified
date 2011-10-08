#ifndef MORTIFIED_CHARACTER_SPRITE_CONTROLLER_HPP
#define MORTIFIED_CHARACTER_SPRITE_CONTROLLER_HPP

#include <memory>

namespace mortified {
    class CharacterActor;
    class Scene;
    class SpriteController;

    std::auto_ptr<SpriteController>
    createCharacterSpriteController(Scene *scene, CharacterActor *actor);
}

#endif
