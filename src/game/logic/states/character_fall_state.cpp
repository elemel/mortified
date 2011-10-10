#include "character_fall_state.hpp"

#include "character_actor.hpp"
#include "character_state_base.hpp"
#include "game.hpp"
#include "math.hpp"
#include "update_handler.hpp"

namespace mortified {
    class CharacterFallState :
        public virtual State,
        public virtual UpdateHandler,
        private virtual CharacterStateBase
    {
    public:
        explicit CharacterFallState(CharacterActor *actor) :
            CharacterStateBase(actor)
        { }

        void enter()
        {
            characterActor_->updateHandler(this);
        }

        void leave()
        {
            characterActor_->updateHandler(0);
        }

        std::auto_ptr<State> transition()
        {
            CharacterSensors const *sensors = characterActor_->sensors();
            if (sensors->floor) {
                return createStandState();
            }
            return std::auto_ptr<State>();
        }

        void update(float dt)
        {
            Vector2 velocity = characterActor_->velocity();
            CharacterSettings const *settings = characterActor_->settings();
            CharacterControls const *controls = characterActor_->controls();

            if (!controls->jump ||
                (characterActor_->jumpTime() + settings->boostDuration <
                 characterActor_->game()->time()))
            {
                characterActor_->boost(false);
            }
            velocity.y += (float(characterActor_->boost()) *
                           settings->boostAcceleration * dt);

            float maxVelocity = std::max(std::abs(velocity.x),
                                         settings->driftVelocity);
            float deltaVelocity = ((float(controls->right) -
                                    float(controls->left)) *
                                   settings->driftAcceleration * dt);
            velocity.x = clamp(velocity.x + deltaVelocity, -maxVelocity,
                               maxVelocity);
            velocity.y = std::max(velocity.y, -settings->fallVelocity);

            characterActor_->velocity(velocity);
            characterActor_->wheelVelocity(velocity.x);
        }
    };

    std::auto_ptr<State> createCharacterFallState(CharacterActor *actor)
    {
        return std::auto_ptr<State>(new CharacterFallState(actor));
    }
}
