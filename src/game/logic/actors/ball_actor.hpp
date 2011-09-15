#ifndef MORTIFIED_BALL_ACTOR_HPP
#define MORTIFIED_BALL_ACTOR_HPP

#include <memory>

namespace mortified {
    class Actor;
    class GameLogic;
    class Vector2;

    std::auto_ptr<Actor>
        createBallActor(GameLogic *logic, Vector2 position, float radius);
}

#endif
