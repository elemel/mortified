#ifndef MORTIFIED_PHYSICS_CONTACT_LISTENER_HPP
#define MORTIFIED_PHYSICS_CONTACT_LISTENER_HPP

#include <Box2D/Box2D.h>

namespace mortified {
    class PhysicsContactListener :
        public b2ContactListener
    {
    public:
    	void BeginContact(b2Contact *contact);

    	void EndContact(b2Contact* contact);
    };
}

#endif
