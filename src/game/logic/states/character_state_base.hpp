#ifndef MORTIFIED_CHARACTER_STATE_BASE_HPP
#define MORTIFIED_CHARACTER_STATE_BASE_HPP

#include "state.hpp"

namespace mortified {
    class CharacterActor;

    class CharacterStateBase :
        public virtual State
    {
    public:
        explicit CharacterStateBase(CharacterActor *actor);

    protected:
        CharacterActor *characterActor_;

        std::auto_ptr<State> createFallState();
        std::auto_ptr<State> createJumpState();
        std::auto_ptr<State> createStandState();
        std::auto_ptr<State> createWalkState();
    };
}

#endif
