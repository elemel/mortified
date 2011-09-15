#ifndef MORTIFIED_PHYSICS_USER_DATA_HPP
#define MORTIFIED_PHYSICS_USER_DATA_HPP

#include <Box2D/Box2D.h>

namespace mortified {
    class Actor;

    Actor *getUserData(b2Fixture *fixture);
    void setUserData(b2Fixture *fixture, Actor *actor);
}

#endif
