#include "physics_contact_listener.hpp"

namespace mortified {
    class PhysicsContactListener : public b2ContactListener {
    public:
        void BeginContact(b2Contact *contact)
        { }
        
        void EndContact(b2Contact* contact)
        { }
    };

    std::auto_ptr<b2ContactListener> createPhysicsContactListener()
    {
        return std::auto_ptr<b2ContactListener>(new PhysicsContactListener);
    }
}
