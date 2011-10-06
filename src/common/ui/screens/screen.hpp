#ifndef MORTIFIED_SCREEN_HPP
#define MORTIFIED_SCREEN_HPP

#include <SDL/SDL.h>

namespace mortified {
    class Screen {
    public:
        virtual ~Screen()
        { }

        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual bool handleEvent(SDL_Event const *event) = 0;

        virtual void update() = 0;
        virtual void draw() = 0;
    };
}

#endif
