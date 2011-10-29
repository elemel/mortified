#ifndef MORTIFIED_EDITOR_SCREEN_HPP
#define MORTIFIED_EDITOR_SCREEN_HPP

#include <memory>

namespace mortified {
    class Screen;
    class Window;

    std::auto_ptr<Screen> createEditorScreen(Window *window);
}

#endif
