#include "character_fall_state.hpp"

#include "actor.hpp"
#include "physics_component.hpp"
#include "property_component.hpp"
#include "state.hpp"
#include "wire.hpp"

#include <iostream>
#include <stdexcept>

namespace mortified {
    class CharacterFallState : public virtual State {
    public:
        explicit CharacterFallState(Actor *actor) :
            actor_(actor),
            propertyComponent_(wire(actor->propertyComponent())),
            physicsComponent_(wire(actor->physicsComponent()))
        { }
        
        virtual char const *name() const
        {
            return "character-fall";
        }
        
        void enter()
        { }
        
        void leave()
        { }
        
        void update(float dt)
        { }
        
        char const *transition()
        {
            return "character-stand";
        }
        
    private:
        Actor *actor_;
        PropertyComponent *propertyComponent_;
        PhysicsComponent *physicsComponent_;
    };
    
    std::auto_ptr<State> createCharacterFallState(Actor *actor)
    {
        return std::auto_ptr<State>(new CharacterFallState(actor));
    }
}
