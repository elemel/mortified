#include "default_window.hpp"

#include "context.hpp"
#include "default_context.hpp"
#include "window.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultWindow : public virtual Window {
    public:
        DefaultWindow() :
            width_(0),
            height_(0),
            fullscreen_(false),
            maximized_(true),
            window_(0)
        { }

        ~DefaultWindow()
        {
            destroy();
        }

        int getWidth() const
        {
            return width_;
        }

        int getHeight() const
        {
            return height_;
        }

        void setSize(int width, int height)
        {
            width_ = width;
            height_ = height;
        }

        bool isFullscreen() const
        {
            return fullscreen_;
        }

        void setFullscreen(bool fullscreen)
        {
            if (window_) {
                if (SDL_SetWindowFullscreen(window_, fullscreen ? SDL_TRUE : SDL_FALSE) == -1) {
                    throw std::runtime_error(std::string("Failed to change fullscreen mode for window: ") +
                                             SDL_GetError());
                }
            }
            fullscreen_ = fullscreen;
        }

        void create()
        {
            destroy();

            if (fullscreen_) {
                SDL_DisplayMode displayMode;
                if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
                    width_ = displayMode.w;
                    height_ = displayMode.h;
                } else {
                    std::cerr << "WARNING: Failed to get current resolution: "
                              << SDL_GetError() << std::endl;
                    std::cerr << "WARNING: Disabling fullscreen mode."
                              << std::endl;
                    fullscreen_ = false;
                }
            }

            window_ = SDL_CreateWindow("Mortified", SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, width_, height_,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                (fullscreen_ ? SDL_WINDOW_FULLSCREEN : 0));
            if (window_ == 0) {
                throw std::runtime_error(std::string("Failed to create window: ") +
                                         SDL_GetError());
            }
            
            if (!fullscreen_ && maximized_) {
                SDL_MaximizeWindow(window_);
            }

            context_ = createContext(window_);
            context_->create();
        }

        void destroy()
        {
            context_.reset();

            if (window_) {
                SDL_DestroyWindow(window_);
                window_ = 0;
            }
        }

        void handleResizeEvent()
        {
            SDL_GetWindowSize(window_, &width_, &height_);
            context_->invalidate();
            context_->create();
        }

        void swapBuffers()
        {
            SDL_GL_SwapWindow(window_);
        }

        boost::intrusive_ptr<Context> getContext()
        {
            return context_;
        }

    private:
        int width_;
        int height_;
        bool fullscreen_;
        bool maximized_;
        SDL_Window *window_;
        boost::intrusive_ptr<Context> context_;
    };

    std::auto_ptr<Window> createWindow()
    {
        return std::auto_ptr<Window>(new DefaultWindow);
    }
}
