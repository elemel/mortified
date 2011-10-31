#include "character_stand_state.hpp"

#include "game_object.hpp"
#include "physics_component.hpp"
#include "state.hpp"

namespace mortified {
    class CharacterStandState : public virtual State {
    public:
        explicit CharacterStandState(GameObject *object) :
            object_(object),
            physicsComponent_(object->physicsComponent())
        { }

        void enter()
        {
            b2RevoluteJoint *joint = physicsComponent_->findRevoluteJoint("motor");
            if (joint) {
                joint->EnableMotor(true);
                joint->SetMaxMotorTorque(100.0f);
                joint->SetMotorSpeed(20.0f);
            }
        }

        void leave()
        { }

        void update(float dt)
        { }

        std::auto_ptr<State> transition()
        {
            return std::auto_ptr<State>();
        }

    private:
        GameObject *object_;
        PhysicsComponent *physicsComponent_;
    };

    std::auto_ptr<State> createCharacterStandState(GameObject *object)
    {
        return std::auto_ptr<State>(new CharacterStandState(object));
    }
}
