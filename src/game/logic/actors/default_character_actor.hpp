#ifndef MORTIFIED_DEFAULT_CHARACTER_ACTOR_HPP
#define MORTIFIED_DEFAULT_CHARACTER_ACTOR_HPP

#include <memory>

namespace mortified {
    class Actor;
    class GameLogic;
    class Vector2;

    std::auto_ptr<Actor>
        createCharacterActor(GameLogic *logic, Vector2 position, float radius);
}

#endif
