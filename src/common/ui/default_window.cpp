#include "default_window.hpp"

#include "context.hpp"
#include "default_context.hpp"
#include "screen.hpp"
#include "window.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultWindow :
        public virtual Window
    {
    public:
        DefaultWindow() :
            width_(0),
            height_(0),
            fullscreen_(false),
            multisample_(false),
            window_(0)
        { }

        ~DefaultWindow()
        {
            destroy();
        }

        int width() const
        {
            return width_;
        }

        int height() const
        {
            return height_;
        }

        void resize(int width, int height)
        {
            width_ = width;
            height_ = height;
        }

        bool fullscreen() const
        {
            return fullscreen_;
        }

        void fullscreen(bool fullscreen)
        {
            fullscreen_ = fullscreen;
        }

        bool multisample() const
        {
            return multisample_;
        }

        void multisample(bool multisample)
        {
            multisample_ = multisample;
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

            context_ = createContext(window_);
            context_->create();
            initContext();
        }

        void destroy()
        {
            removeAllScreens();

            context_.reset();

            if (window_) {
                SDL_DestroyWindow(window_);
                window_ = 0;
            }
        }

        void addScreen(std::auto_ptr<Screen> screen)
        {
            assert(screen.get());
            screens_.push_back(screen.release());
            screens_.back()->create();
        }

        std::auto_ptr<Screen> removeScreen(Screen *screen)
        {
            assert(screen);
            for (std::size_t i = screens_.size(); i > 0; --i) {
                if (screens_[i - 1] == screen) {
                    screens_[i - 1] = 0;
                    while (!screens_.empty() && screens_.back() == 0) {
                        screens_.pop_back();
                    }

                    std::auto_ptr<Screen> result(screen);
                    result->destroy();
                    return result;
                }
            }
            return std::auto_ptr<Screen>();
        }

        Screen *currentScreen()
        {
            assert(screens_.empty() || screens_.back());
            return !screens_.empty() ? screens_.back() : 0;
        }

        bool handleEvent(SDL_Event const *event)
        {
            bool handled = false;
            if (event->type == SDL_WINDOWEVENT &&
                event->window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SDL_GetWindowSize(window_, &width_, &height_);
                handled = true;
                context_->invalidate();
                context_->create();
                initContext();
                if (Screen *screen = currentScreen()) {
                    screen->resize(width_, height_);
                }
            }
            if (!handled) {
                if (Screen *screen = currentScreen()) {
                    handled = screen->handleEvent(event);
                }
            }
            return handled;
        }

        void update()
        {
            if (Screen *screen = currentScreen()) {
                screen->update();
            }
        }

        void draw()
        {
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);
            if (Screen *screen = currentScreen()) {
                screen->draw();
            }
            SDL_GL_SwapWindow(window_);
        }

    private:
        int width_;
        int height_;
        bool fullscreen_;
        bool multisample_;
        SDL_Window *window_;
        std::auto_ptr<Context> context_;
        std::vector<Screen *> screens_;

        void initContext()
        {
            if (SDL_GL_SetSwapInterval(1) == -1) {
                std::cerr << "WARNING: Failed to enable vertical sync: "
                          << SDL_GetError() << std::endl;
            }
            if (multisample_) {
                glEnable(GL_MULTISAMPLE);
            }
        }

        void removeAllScreens()
        {
            while (currentScreen()) {
                removeScreen(currentScreen());
            }
        }
    };

    std::auto_ptr<Window> createWindow()
    {
        return std::auto_ptr<Window>(new DefaultWindow);
    }
}