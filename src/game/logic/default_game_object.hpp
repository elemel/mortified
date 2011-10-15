#ifndef MORTIFIED_DEFAULT_GAME_OBJECT_HPP
#define MORTIFIED_DEFAULT_GAME_OBJECT_HPP

#include "math.hpp"

#include <boost/shared_ptr.hpp>

namespace mortified {
    class Game;
    class GameObject;

    boost::shared_ptr<GameObject>
    createGameObject(Game *game, Matrix3 transform = Matrix3());
}
#endif
