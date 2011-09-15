#include "character_stand_state.hpp"

#include "character_actor.hpp"
#include "character_state_base.hpp"

namespace mortified {
    class CharacterStandState :
        public virtual State,
        private virtual CharacterStateBase
    {
    public:
        CharacterStandState(CharacterActor *actor) :
            CharacterStateBase(actor)
        { }

        void enter()
        {
            characterActor_->wheelMotorEnabled(true);
            characterActor_->wheelMotorVelocity(0.0f);
        }

        void leave()
        {
            characterActor_->wheelMotorEnabled(false);
        }

        std::auto_ptr<State> transition()
        {
            CharacterControls const *controls = characterActor_->controls();
            CharacterSensors const *sensors = characterActor_->sensors();
            if (!sensors->floor) {
                return createFallState();
            }
            if (controls->jump) {
                return createJumpState();
            }
            if (int(controls->right) - int(controls->left)) {
                return createWalkState();
            }
            return std::auto_ptr<State>();
        }
    };

    std::auto_ptr<State> createCharacterStandState(CharacterActor *actor)
    {
        return std::auto_ptr<State>(new CharacterStandState(actor));
    }
}
