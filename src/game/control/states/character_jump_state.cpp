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
            propertyComponent_(wire(actor->getPropertyComponent())),
            physicsComponent_(wire(actor->getPhysicsComponent())),
            jumpInput_(wire(propertyComponent_->findBool("jump-input"))),
            bodyBody_(wire(physicsComponent_->findBody("body")))
        { }
        
        virtual char const *getName() const
        {
            return "character-jump";
        }
        
        void enter()
        {
            b2Vec2 linearVelocity = bodyBody_->GetLinearVelocity();
            linearVelocity.y = 10.0f;
            bodyBody_->SetLinearVelocity(linearVelocity);
        }
        
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
        b2Body *bodyBody_;
    };
    
    std::auto_ptr<State> createCharacterJumpState(Actor *actor)
    {
        return std::auto_ptr<State>(new CharacterJumpState(actor));
    }
}
