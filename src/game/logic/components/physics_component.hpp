#ifndef MORTIFIED_PHYSICS_COMPONENT_HPP
#define MORTIFIED_PHYSICS_COMPONENT_HPP

#include "component.hpp"

#include <list>
#include <Box2D/Box2D.h>

namespace mortified {
    class PhysicsComponent : public virtual Component {
    public:
        typedef std::list<b2Body *> BodyList;
        typedef std::list<b2Joint *> JointList;
    };
}

#endif
