#ifndef MORTIFIED_DEFAULT_CONTEXT_HPP
#define MORTIFIED_DEFAULT_CONTEXT_HPP

#include <SDL/SDL.h>

#include <memory>

namespace mortified {
    class Context;

    std::auto_ptr<Context> createContext(SDL_Window *window);
}

#endif
