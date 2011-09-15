#include "character_jump_state.hpp"

#include "character_actor.hpp"
#include "character_state_base.hpp"
#include "game_logic.hpp"
#include "math.hpp"

namespace mortified {
    class CharacterJumpState :
        public virtual State,
        private virtual CharacterStateBase
    {
    public:
        explicit CharacterJumpState(CharacterActor *actor) :
            CharacterStateBase(actor)
        { }

        void enter()
        {
            Vector2 velocity = characterActor_->velocity();
            velocity.y = characterActor_->settings()->jumpVelocity;
            characterActor_->velocity(velocity);
            characterActor_->jumpTime(characterActor_->gameLogic()->time());
            characterActor_->boost(true);
        }

        void leave()
        { }

        std::auto_ptr<State> transition()
        {
            return createFallState();
        }
    };

    std::auto_ptr<State> createCharacterJumpState(CharacterActor *actor)
    {
        return std::auto_ptr<State>(new CharacterJumpState(actor));
    }
}
