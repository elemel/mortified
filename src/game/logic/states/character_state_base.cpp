#include "character_state_base.hpp"

#include "character_fall_state.hpp"
#include "character_jump_state.hpp"
#include "character_stand_state.hpp"
#include "character_walk_state.hpp"

namespace mortified {
    CharacterStateBase::CharacterStateBase(CharacterActor *actor) :
        characterActor_(actor)
    { }

    std::auto_ptr<State> CharacterStateBase::createFallState()
    {
        return createCharacterFallState(characterActor_);
    }

    std::auto_ptr<State> CharacterStateBase::createJumpState()
    {
        return createCharacterJumpState(characterActor_);
    }

    std::auto_ptr<State> CharacterStateBase::createStandState()
    {
        return createCharacterStandState(characterActor_);
    }

    std::auto_ptr<State> CharacterStateBase::createWalkState()
    {
        return createCharacterWalkState(characterActor_);
    }
}
