#include "physics_contact_listener.hpp"

#include "actor.hpp"
#include "physics_user_data.hpp"

#include <iostream>

namespace mortified {
    void PhysicsContactListener::BeginContact(b2Contact *contact)
    {
        if (Actor *actor = getUserData(contact->GetFixtureA())) {
            actor->addContact(contact);
        }
        if (Actor *actor = getUserData(contact->GetFixtureB())) {
            actor->addContact(contact);
        }
    }
    
    void PhysicsContactListener::EndContact(b2Contact *contact)
    {
        if (Actor *actor = getUserData(contact->GetFixtureA())) {
            actor->removeContact(contact);
        }
        if (Actor *actor = getUserData(contact->GetFixtureB())) {
            actor->removeContact(contact);
        }
    }
}
