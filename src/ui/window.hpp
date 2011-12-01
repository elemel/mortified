#ifndef MORTIFIED_WINDOW_HPP
#define MORTIFIED_WINDOW_HPP

#include <memory>
#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL.h>

namespace mortified {
    class Context;

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

        virtual void handleResizeEvent() = 0;
        virtual void swapBuffers() = 0;

        virtual boost::intrusive_ptr<Context> getContext() = 0;
    };
}

#endif
