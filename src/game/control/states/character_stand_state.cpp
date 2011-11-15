#include "character_stand_state.hpp"

#include "actor.hpp"
#include "physics_component.hpp"
#include "property_component.hpp"
#include "state.hpp"
#include "wire.hpp"

#include <iostream>
#include <stdexcept>

namespace mortified {
    class CharacterStandState : public virtual State {
    public:
        explicit CharacterStandState(Actor *actor) :
            actor_(actor),
            propertyComponent_(wire(actor->getPropertyComponent())),
            physicsComponent_(wire(actor->getPhysicsComponent())),
            leftInput_(wire(propertyComponent_->findBool("left-input"))),
            rightInput_(wire(propertyComponent_->findBool("right-input"))),
            jumpInput_(wire(propertyComponent_->findBool("jump-input"))),
            motorJoint_(wire(physicsComponent_->findRevoluteJoint("motor")))
        { }

        virtual char const *getName() const
        {
            return "character-stand";
        }

        void enter()
        {
            motorJoint_->EnableMotor(true);
            motorJoint_->SetMotorSpeed(0);
        }

        void leave()
        {
            motorJoint_->EnableMotor(false);
        }

        void update(float dt)
        { }

        char const *transition()
        {
            if (*jumpInput_) {
                return "character-jump";
            }
            if (*leftInput_ || *rightInput_) {
                return "character-walk";
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

    std::auto_ptr<State> createCharacterStandState(Actor *actor)
    {
        return std::auto_ptr<State>(new CharacterStandState(actor));
    }
}
