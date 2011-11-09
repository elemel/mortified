#include "character_walk_state.hpp"

#include "actor.hpp"
#include "physics_component.hpp"
#include "property_component.hpp"
#include "state.hpp"
#include "wire.hpp"

#include <iostream>
#include <stdexcept>

namespace mortified {
    class CharacterWalkState : public virtual State {
    public:
        explicit CharacterWalkState(Actor *actor) :
            actor_(actor),
            propertyComponent_(wire(actor->propertyComponent())),
            physicsComponent_(wire(actor->physicsComponent())),
            leftInput_(wire(propertyComponent_->findBool("left-input"))),
            rightInput_(wire(propertyComponent_->findBool("right-input"))),
            jumpInput_(wire(propertyComponent_->findBool("jump-input"))),
            motorJoint_(wire(physicsComponent_->findRevoluteJoint("motor")))
        { }

        virtual char const *name() const
        {
            return "character-walk";
        }

        void enter()
        {
            motorJoint_->EnableMotor(true);
        }

        void leave()
        {
            motorJoint_->EnableMotor(false);
        }

        void update(float dt)
        {
            float speed = 10.0f * (float(*leftInput_) - float(*rightInput_));
            motorJoint_->SetMotorSpeed(speed);
        }

        char const *transition()
        {
            if (*jumpInput_) {
                return "character-jump";
            }
            if (!*leftInput_ && !*rightInput_) {
                return "character-stand";
            }
            return 0;
        }

    private:
        Actor *actor_;
        PropertyComponent *propertyComponent_;
        PhysicsComponent *physicsComponent_;
        bool *leftInput_;
        bool *rightInput_;
        bool *jumpInput_;
        b2RevoluteJoint *motorJoint_;
    };

    std::auto_ptr<State> createCharacterWalkState(Actor *actor)
    {
        return std::auto_ptr<State>(new CharacterWalkState(actor));
    }
}
