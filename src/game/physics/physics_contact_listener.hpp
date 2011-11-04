#ifndef MORTIFIED_PHYSICS_CONTACT_LISTENER_HPP
#define MORTIFIED_PHYSICS_CONTACT_LISTENER_HPP

#include <memory>
#include <Box2D/Box2D.h>

namespace mortified {
    std::auto_ptr<b2ContactListener> createPhysicsContactListener();
}

#endif
