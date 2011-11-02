#ifndef MORTIFIED_CHARACTER_STAND_STATE_HPP
#define MORTIFIED_CHARACTER_STAND_STATE_HPP

#include <memory>

namespace mortified {
    class Actor;
    class State;

    std::auto_ptr<State> createCharacterStandState(Actor *actor);
}

#endif
