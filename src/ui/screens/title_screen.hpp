#ifndef MORTIFIED_TITLE_SCREEN_HPP
#define MORTIFIED_TITLE_SCREEN_HPP

#include <memory>

namespace mortified {
    class Application;
    class Screen;
    
    std::auto_ptr<Screen> createTitleScreen(Application *application);
}

#endif
