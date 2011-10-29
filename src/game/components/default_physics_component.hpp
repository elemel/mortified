#ifndef MORTIFIED_DEFAULT_PHYSICS_COMPONENT_HPP
#define MORTIFIED_DEFAULT_PHYSICS_COMPONENT_HPP

#include <memory>

namespace mortified {
    class GameObject;
    class PhysicsComponent;

    std::auto_ptr<PhysicsComponent> createPhysicsComponent(GameObject *object);
}

#endif
