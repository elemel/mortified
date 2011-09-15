#ifndef MORTIFIED_PLATFORM_ACTOR_HPP
#define MORTIFIED_PLATFORM_ACTOR_HPP

#include <memory>

namespace mortified {
    class Actor;
    class GameLogic;
    class Vector2;

    std::auto_ptr<Actor>
        createPlatformActor(GameLogic *logic, Vector2 position, Vector2 size,
                            float angle = 0.0f);
}

#endif
