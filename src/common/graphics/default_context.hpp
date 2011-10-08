#ifndef MORTIFIED_DEFAULT_CONTEXT_HPP
#define MORTIFIED_DEFAULT_CONTEXT_HPP

#include <memory>
#include <boost/shared_ptr.hpp>
#include <SDL/SDL.h>

namespace mortified {
    class Context;

    boost::shared_ptr<Context>
        createContext(SDL_Window *window, bool multisample);
}

#endif
