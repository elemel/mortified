#include "character_stand_state.hpp"

#include "actor.hpp"
#include "physics_component.hpp"
#include "property_component.hpp"
#include "state.hpp"

#include <iostream>
#include <stdexcept>

namespace mortified {
    namespace {
        template <typename T>
        T *check(T *ptr)
        {
            if (ptr == 0) {
                throw std::runtime_error("Null pointer.");
            }
            return ptr;
        }
    }

    class CharacterStandState : public virtual State {
    public:
        explicit CharacterStandState(Actor *actor) :
            actor_(actor),
            propertyComponent_(check(actor->propertyComponent())),
            physicsComponent_(check(actor->physicsComponent())),
            leftInput_(check(propertyComponent_->findBool("left-input"))),
            rightInput_(check(propertyComponent_->findBool("right-input"))),
            motorJoint_(check(physicsComponent_->findRevoluteJoint("motor")))
        { }

        void enter()
        {
            motorJoint_->EnableMotor(true);
            motorJoint_->SetMaxMotorTorque(50.0);
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

        std::auto_ptr<State> transition()
        {
            return std::auto_ptr<State>();
        }

    private:
        Actor *actor_;
        PropertyComponent *propertyComponent_;
        PhysicsComponent *physicsComponent_;
        bool *leftInput_;
        bool *rightInput_;
        b2RevoluteJoint *motorJoint_;
    };

    std::auto_ptr<State> createCharacterStandState(Actor *actor)
    {
        return std::auto_ptr<State>(new CharacterStandState(actor));
    }
}
