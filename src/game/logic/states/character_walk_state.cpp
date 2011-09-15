#include "character_walk_state.hpp"

#include "character_actor.hpp"
#include "character_state_base.hpp"
#include "update_handler.hpp"

namespace mortified {
    class CharacterWalkState :
        public virtual State,
        public virtual UpdateHandler,
        private virtual CharacterStateBase
    {
    public:
        explicit CharacterWalkState(CharacterActor *actor) :
            CharacterStateBase(actor)
        { }

        void enter()
        {
            characterActor_->updateHandler(this);
            characterActor_->wheelMotorEnabled(true);
        }

        void leave()
        {
            characterActor_->wheelMotorEnabled(false);
            characterActor_->updateHandler(0);
        }

        std::auto_ptr<State> transition()
        {
            CharacterSensors const *sensors = characterActor_->sensors();
            CharacterControls const *controls = characterActor_->controls();
            if (!sensors->floor) {
                return createFallState();;
            }
            if (controls->jump) {
                return createJumpState();
            }
            if (int(controls->right) - int(controls->left) == 0) {
                return createStandState();
            }
            return std::auto_ptr<State>();
        }

        void update(float dt)
        {
            (void) dt;

            CharacterControls const *controls = characterActor_->controls();
            float velocity =
                (characterActor_->settings()->walkVelocity *
                 (float(controls->right) - float(controls->left)));
            characterActor_->wheelMotorVelocity(velocity);
        }
    };

    std::auto_ptr<State> createCharacterWalkState(CharacterActor *actor)
    {
        return std::auto_ptr<State>(new CharacterWalkState(actor));
    }
}
