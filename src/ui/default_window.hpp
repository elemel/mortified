#ifndef MORTIFIED_DEFAULT_WINDOW_HPP
#define MORTIFIED_DEFAULT_WINDOW_HPP

#include <memory>

namespace mortified {
    class Window;

    std::auto_ptr<Window> createWindow();
}

#endif
