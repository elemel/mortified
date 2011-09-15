#ifndef MORTIFIED_CHARACTER_WALK_STATE_HPP
#define MORTIFIED_CHARACTER_WALK_STATE_HPP

#include <memory>

namespace mortified {
    class CharacterActor;
    class State;

    std::auto_ptr<State> createCharacterWalkState(CharacterActor *actor);
}

#endif
