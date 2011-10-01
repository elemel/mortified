#ifndef MORTIFIED_TITLE_SCREEN_HPP
#define MORTIFIED_TITLE_SCREEN_HPP

#include <memory>

namespace mortified {
    class Screen;
    class Window;
    
    std::auto_ptr<Screen> createTitleScreen(Window *window);
}

#endif
