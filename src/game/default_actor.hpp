#ifndef MORTIFIED_DEFAULT_ACTOR_HPP
#define MORTIFIED_DEFAULT_ACTOR_HPP

#include "math.hpp"

#include <boost/shared_ptr.hpp>

namespace mortified {
    class Actor;
    class Game;

    boost::shared_ptr<Actor> createActor(Game *game);
}
#endif
