#ifndef MORTIFIED_DEFAULT_CONTEXT_HPP
#define MORTIFIED_DEFAULT_CONTEXT_HPP

#include <memory>
#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL.h>

namespace mortified {
    class Context;

    boost::intrusive_ptr<Context> createContext(SDL_Window *window);
}

#endif
