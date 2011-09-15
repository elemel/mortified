#ifndef MORTIFIED_GAME_SCREEN_HPP
#define MORTIFIED_GAME_SCREEN_HPP

#include <memory>

namespace mortified {
    class Screen;
    class Window;

    std::auto_ptr<Screen> createGameScreen(Window *window, bool supersample);
}

#endif
