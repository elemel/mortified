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
            window_.reset();
            TTF_Quit();
            SDL_Quit();
        }

        int main(int argc, char **argv)
        {
            parseCommandLine(argc, argv);
            initSdl();
            window_ = createWindow();
            window_->resize(640, 480);
            window_->setFullscreen(settings_.fullscreen);
            window_->create();
            if (settings_.editor) {
                window_->addScreen(createEditorScreen(window_.get()));
            } else if (settings_.game) {
                window_->addScreen(createGameScreen(window_.get(),
                                                    settings_.supersample));
            } else {
                window_->addScreen(createTitleScreen(window_.get()));
            }
            eventLoop();
            return 0;
        }

    private:
        ApplicationSettings settings_;
        std::auto_ptr<Window> window_;

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
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0) {
                throw std::runtime_error(std::string() +
                                         "Failed to initialize SDL: " +
                                         SDL_GetError());
            }

            if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0) {
                std::cerr << "WARNING: Failed to enable double buffering: "
                          << SDL_GetError() << std::endl;
            }

            TTF_Init();
        }

        void eventLoop()
        {
            while (window_->getCurrentScreen()) {
                handleEvents();
                window_->update();
                window_->draw();
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
            bool handled = window_->handleEvent(event);
            if (!handled) {
                switch (event->type) {
                case SDL_KEYDOWN:
                    if (event->key.keysym.sym == SDLK_ESCAPE) {
                        if (Screen *screen = window_->getCurrentScreen()) {
                            window_->removeScreen(screen);
                        }
                    }
                    break;
                }
            }
        }
    };

    std::auto_ptr<Application> createApplication()
    {
        return std::auto_ptr<Application>(new DefaultApplication);
    }
}
