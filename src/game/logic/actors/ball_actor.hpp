#ifndef MORTIFIED_BALL_ACTOR_HPP
#define MORTIFIED_BALL_ACTOR_HPP

#include <memory>

namespace mortified {
    class Actor;
    class Game;
    class Vector2;

    std::auto_ptr<Actor>
    createBallActor(Game *game, Vector2 position, float radius);
}

#endif
