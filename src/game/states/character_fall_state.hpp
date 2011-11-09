#ifndef MORTIFIED_CHARACTER_FALL_STATE_HPP
#define MORTIFIED_CHARACTER_FALL_STATE_HPP

#include <memory>

namespace mortified {
    class Actor;
    class State;
    
    std::auto_ptr<State> createCharacterFallState(Actor *actor);
}

#endif
