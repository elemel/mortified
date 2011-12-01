#ifndef MORTIFIED_GAME_SCREEN_HPP
#define MORTIFIED_GAME_SCREEN_HPP

#include <memory>

namespace mortified {
    class Application;
    class Screen;

    std::auto_ptr<Screen>
    createGameScreen(Application *application, bool supersample);
}

#endif
