#ifndef MORTIFIED_EDITOR_SCREEN_HPP
#define MORTIFIED_EDITOR_SCREEN_HPP

#include <memory>

namespace mortified {
    class Application;
    class Screen;

    std::auto_ptr<Screen> createEditorScreen(Application *application);
}

#endif
