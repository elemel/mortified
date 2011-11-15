#ifndef MORTIFIED_DEFAULT_ACTOR_HPP
#define MORTIFIED_DEFAULT_ACTOR_HPP

#include "math.hpp"

#include <memory>

namespace mortified {
    class Actor;
    class Game;

    std::auto_ptr<Actor> createActor(Game *game);
}

#endif
