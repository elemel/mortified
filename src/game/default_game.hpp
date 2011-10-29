#ifndef MORTIFIED_DEFAULT_GAME_HPP
#define MORTIFIED_DEFAULT_GAME_HPP

#include <memory>

namespace mortified {
    class Game;

    std::auto_ptr<Game> createGame();
}

#endif
