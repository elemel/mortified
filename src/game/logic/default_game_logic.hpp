#ifndef MORTIFIED_DEFAULT_GAME_LOGIC_HPP
#define MORTIFIED_DEFAULT_GAME_LOGIC_HPP

#include <memory>

namespace mortified {
    class GameLogic;

    std::auto_ptr<GameLogic> createGameLogic();
}

#endif
