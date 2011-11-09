#ifndef MORTIFIED_DEFAULT_GAME_HPP
#define MORTIFIED_DEFAULT_GAME_HPP

#include <memory>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Game;

    std::auto_ptr<Game> createGame(boost::intrusive_ptr<Context> context);
}

#endif
