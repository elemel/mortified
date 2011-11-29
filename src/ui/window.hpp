#ifndef MORTIFIED_WINDOW_HPP
#define MORTIFIED_WINDOW_HPP

#include <memory>
#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL.h>

namespace mortified {
    class Context;
    class Screen;

    class Window {
    public:
        virtual ~Window()
        { }

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual void setSize(int width, int height) = 0;

        virtual bool isFullscreen() const = 0;
        virtual void setFullscreen(bool fullscreen) = 0;

        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual void addScreen(std::auto_ptr<Screen> screen) = 0;
        virtual std::auto_ptr<Screen> removeScreen(Screen *screen) = 0;
        virtual Screen *getCurrentScreen() = 0;

        virtual bool handleEvent(SDL_Event const *event) = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        virtual boost::intrusive_ptr<Context> getContext() = 0;
    };
}

#endif
