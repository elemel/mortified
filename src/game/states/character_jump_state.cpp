#include "character_jump_state.hpp"

#include "actor.hpp"
#include "physics_component.hpp"
#include "property_component.hpp"
#include "state.hpp"
#include "wire.hpp"

#include <iostream>
#include <stdexcept>

namespace mortified {
    class CharacterJumpState : public virtual State {
    public:
        explicit CharacterJumpState(Actor *actor) :
            actor_(actor),
            propertyComponent_(wire(actor->propertyComponent())),
            physicsComponent_(wire(actor->physicsComponent())),
            jumpInput_(wire(propertyComponent_->findBool("jump-input")))
        { }
        
        virtual char const *name() const
        {
            return "character-jump";
        }
        
        void enter()
        { }
        
        void leave()
        { }
        
        void update(float dt)
        { }
        
        char const *transition()
        {
            if (!*jumpInput_) {
                return "character-fall";
            }
            return 0;
        }
        
    private:
        Actor *actor_;
        PropertyComponent *propertyComponent_;
        PhysicsComponent *physicsComponent_;
        bool *jumpInput_;
    };
    
    std::auto_ptr<State> createCharacterJumpState(Actor *actor)
    {
        return std::auto_ptr<State>(new CharacterJumpState(actor));
    }
}
