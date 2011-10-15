#ifndef MORTIFIED_DEFAULT_PHYSICS_COMPONENT_HPP
#define MORTIFIED_DEFAULT_PHYSICS_COMPONENT_HPP

#include <boost/shared_ptr.hpp>

namespace mortified {
    class GameObject;
    class PhysicsComponent;

    boost::shared_ptr<PhysicsComponent>
    createPhysicsComponent(GameObject *object);
}

#endif
