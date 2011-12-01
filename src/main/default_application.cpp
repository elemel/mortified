#include "default_application.hpp"

#include "application.hpp"
#include "default_window.hpp"
#include "editor_screen.hpp"
#include "game_screen.hpp"
#include "screen.hpp"
#include "title_screen.hpp"
#include "window.hpp"

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>

namespace mortified {
    class ApplicationSettings {
    public:
        bool drawPhysics;
        bool editor;
        bool fullscreen;
        bool game;
        bool supersample;

        ApplicationSettings();
    };

    ApplicationSettings::ApplicationSettings() :
        drawPhysics(false),
        editor(false),
        fullscreen(false),
        game(false),
        supersample(false)
    { }

    class DefaultApplication : public virtual Application {
    public:
        DefaultApplication() :
            window_(0)
        { }

        ~DefaultApplication()
        {
            while (!screens_.empty()) {
                screens_.back()->destroy();
                delete screens_.back();
                screens_.pop_back();
            }
            window_.reset();

            TTF_Quit();
            Mix_CloseAudio();
            Mix_Quit();
            SDL_Quit();
        }

        int main(int argc, char **argv)
        {
            parseCommandLine(argc, argv);
            initSdl();
            window_ = createWindow();
            window_->setSize(640, 480);
            window_->setFullscreen(settings_.fullscreen);
            window_->create();
            if (settings_.editor) {
                addScreen(createEditorScreen(this));
            } else if (settings_.game) {
                addScreen(createGameScreen(this, settings_.supersample));
            } else {
                addScreen(createTitleScreen(this));
            }
            eventLoop();
            return 0;
        }

        Screen *getCurrentScreen()
        {
            return screens_.empty() ? 0 : screens_.back();
        }
        
        void addScreen(std::auto_ptr<Screen> screen)
        {
            screens_.push_back(screen.release());
            screens_.back()->create();
        }
        
        std::auto_ptr<Screen> removeScreen(Screen *screen)
        {
            ScreenIterator i = std::find(screens_.begin(), screens_.end(), screen);
            assert(i != screens_.end());
            screens_.erase(i);

            std::auto_ptr<Screen> result(screen);
            result->destroy();
            return result;
        }

        Window *getWindow()
        {
            return window_.get();
        }

        Window const *getWindow() const
        {
            return window_.get();
        }

    private:
        ApplicationSettings settings_;
        std::auto_ptr<Window> window_;
        ScreenList screens_;

        void parseCommandLine(int argc, char **argv)
        {
            for (int i = 1; i < argc; ++i) {
                if (strcmp(argv[i], "--draw-physics") == 0) {
                    settings_.drawPhysics = true;
                }
                if (strcmp(argv[i], "--editor") == 0) {
                    settings_.editor = true;
                }
                if (strcmp(argv[i], "--fullscreen") == 0) {
                    settings_.fullscreen = true;
                }
                if (strcmp(argv[i], "--game") == 0) {
                    settings_.game = true;
                }
                if (strcmp(argv[i], "--windowed") == 0) {
                    settings_.fullscreen = false;
                }
                if (strcmp(argv[i], "--supersample") == 0) {
                    settings_.supersample = true;
                }
            }
        }

        void initSdl()
        {
            if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
                throw std::runtime_error(std::string() +
                                         "Failed to initialize SDL: " +
                                         SDL_GetError());
            }

            if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1) {
                std::cerr << "WARNING: Failed to enable double buffering: "
                          << SDL_GetError() << std::endl;
            }

            if (Mix_Init(MIX_INIT_OGG) == -1) {
                throw std::runtime_error(std::string() +
                                         "Failed to initialize sounds: " +
                                         Mix_GetError());
            }

            if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
                throw std::runtime_error(std::string() +
                                         "Failed to initialize sounds: " +
                                         Mix_GetError());
            }

            if (TTF_Init() == -1) {
                throw std::runtime_error(std::string() +
                                         "Failed to initialize fonts: " +
                                         TTF_GetError());
            }
        }

        void eventLoop()
        {
            while (!screens_.empty()) {
                handleEvents();
                update();
                draw();
            }
        }

        void handleEvents()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                handleEvent(&event);
            }
        }

        void handleEvent(SDL_Event *event)
        {
            assert(event);
            bool handled = false;
            if (event->type == SDL_WINDOWEVENT &&
                event->window.event == SDL_WINDOWEVENT_RESIZED)
            {
                window_->handleResizeEvent();
                handled = true;
            }
            if (!screens_.empty()) {
                handled = screens_.back()->handleEvent(event);
            }
            if (!handled) {
                switch (event->type) {
                case SDL_KEYDOWN:
                    if (event->key.keysym.sym == SDLK_ESCAPE) {
                        if (!screens_.empty()) {
                            removeScreen(screens_.back());
                        }
                    }
                    if (event->key.keysym.sym == SDLK_RETURN &&
                        event->key.keysym.mod & (KMOD_CTRL | KMOD_ALT | KMOD_META))
                    {
                        window_->setFullscreen(!window_->isFullscreen());
                    }
                    break;
                }
            }
        }

        void update()
        {
            if (!screens_.empty()) {
                screens_.back()->update();
            }
        }

        void draw()
        {
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if (!screens_.empty()) {
                screens_.back()->draw();
            }
            window_->swapBuffers();
        }
    };

    std::auto_ptr<Application> createApplication()
    {
        return std::auto_ptr<Application>(new DefaultApplication);
    }
}
