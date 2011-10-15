#ifndef MORTIFIED_DEFAULT_CHARACTER_ACTOR_HPP
#define MORTIFIED_DEFAULT_CHARACTER_ACTOR_HPP

#include <memory>

namespace mortified {
    class Actor;
    class Game;
    class Vector2;

    std::auto_ptr<Actor>
    createCharacterActor(Game *game, Vector2 position, float radius);
}

#endif
