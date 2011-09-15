
#include "game_screen.hpp"

#include "actor.hpp"
#include "camera.hpp"
#include "character_actor.hpp"
#include "character_sprite_controller.hpp"
#include "default_camera.hpp"
#include "default_character_actor.hpp"
#include "default_game_logic.hpp"
#include "default_framebuffer.hpp"
#include "default_scene_graph.hpp"
#include "framebuffer.hpp"
#include "game_logic.hpp"
#include "math.hpp"
#include "physics_draw.hpp"
#include "platform_actor.hpp"
#include "scene_graph.hpp"
#include "screen.hpp"
#include "sprite_controller.hpp"
#include "window.hpp"

#include <memory>
#include <iostream>
#include <stdexcept>
#include <Box2D/Box2D.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class GameScreen :
        public virtual Screen
    {
    public:
        explicit GameScreen(Window *window, bool supersample);

        void create();
        void destroy();

        bool handleEvent(SDL_Event const *event);

        void update();
        void draw();

        void resize(int width, int height);

    private:
        Window *window_;
        bool supersample_;
        float updateTime_;
        float dt_;
        std::auto_ptr<GameLogic> gameLogic_;
        std::auto_ptr<b2Draw> physicsDraw_;
        std::auto_ptr<SceneGraph> sceneGraph_;
        std::auto_ptr<Framebuffer> framebuffer_;
        std::auto_ptr<Camera> camera_;

        void skipFrames(float time);
        void updateControls();
        void updateGame(float time);
        void updateCamera();
        void drawScene();
        void drawSceneToFramebuffer();
        void drawFramebufferToScreen();
        void drawPhysics();
    };

    GameScreen::GameScreen(Window *window, bool supersample) :
        window_(window),
        supersample_(supersample),
        updateTime_(0.0f),
        dt_(1.0f / 60.0f)
    { }

    void GameScreen::create()
    {
        gameLogic_ = createGameLogic();
        physicsDraw_.reset(new PhysicsDraw);
        sceneGraph_ = createSceneGraph();
        camera_ = createCamera();
        camera_->scale(5.0f);

        gameLogic_->addActor(createPlatformActor(gameLogic_.get(), Vector2(0.0f, -2.0f), Vector2(1.0f, 0.1f), 0.1f));
        gameLogic_->addActor(createPlatformActor(gameLogic_.get(), Vector2(4.0f, -2.5f), Vector2(1.0f, 0.1f), -0.2f));
        gameLogic_->addActor(createPlatformActor(gameLogic_.get(), Vector2(9.0f, -2.0f), Vector2(1.0f, 0.1f), 0.0f));
        gameLogic_->addActor(createPlatformActor(gameLogic_.get(), Vector2(13.0f, -1.5f), Vector2(1.0f, 0.1f), -0.1f));
        gameLogic_->addActor(createPlatformActor(gameLogic_.get(), Vector2(18.0f, -2.5f), Vector2(1.0f, 0.1f), 0.2f));

        std::auto_ptr<Actor> heroAsActor =
            createCharacterActor(gameLogic_.get(), Vector2(0.0f, 2.0f), 0.5f);
        CharacterActor *heroAsCharacterActor = heroAsActor->asCharacterActor();
        gameLogic_->addActor(heroAsActor);
        gameLogic_->hero(heroAsCharacterActor);

        std::auto_ptr<SpriteController> characterSpriteController =
            createCharacterSpriteController(sceneGraph_.get(), heroAsCharacterActor);
        sceneGraph_->addSpriteController(characterSpriteController);

        resize(window_->width(), window_->height());
    }

    void GameScreen::destroy()
    {
        framebuffer_.reset();
    }

    bool GameScreen::handleEvent(SDL_Event const *event)
    {
        if (event->type == SDL_KEYDOWN &&
            event->key.keysym.sym == SDLK_BACKSPACE)
        {
            destroy();
            create();
            return true;
        }
        return false;
    }

    void GameScreen::update()
    {
        float time = 0.001f * SDL_GetTicks();
        skipFrames(time);
        updateControls();
        updateGame(time);
        sceneGraph_->update();
    }

    void GameScreen::draw()
    {
        updateCamera();
        if (supersample_) {
            drawSceneToFramebuffer();
            drawFramebufferToScreen();
        } else {
            drawScene();
        }
        drawPhysics();
    }

    void GameScreen::resize(int width, int height)
    {
        if (framebuffer_.get()) {
            framebuffer_->invalidate();
        }
        framebuffer_ = createFramebuffer(2 * width, 2 * height);
        camera_->aspectRatio(float(width) / float(height));
    }

    void GameScreen::skipFrames(float time)
    {
        if (time - updateTime_ >= 10.0f * dt_) {
            int skip = int((time - updateTime_) / dt_);
            updateTime_ += float(skip) * dt_;
            std::cerr << "WARNING: Skipped " << skip << " frame(s)." << std::endl;
        }
        assert(time - updateTime_ <= 10.0f * dt_);
    }

    void GameScreen::updateControls()
    {
        if (CharacterActor *hero = gameLogic_->hero()) {
            Uint8 *state = SDL_GetKeyboardState(NULL);
            CharacterControls controls;
            controls.up = state[SDL_SCANCODE_W] | state[SDL_SCANCODE_UP];
            controls.left = state[SDL_SCANCODE_A] | state[SDL_SCANCODE_LEFT];
            controls.down = state[SDL_SCANCODE_S] | state[SDL_SCANCODE_DOWN];
            controls.right = state[SDL_SCANCODE_D] | state[SDL_SCANCODE_RIGHT];
            controls.jump = state[SDL_SCANCODE_SPACE];
            hero->controls(&controls);
        }
    }

    void GameScreen::updateGame(float time)
    {
        while (time - updateTime_ >= dt_) {
            updateTime_ += dt_;
            gameLogic_->update(dt_);
        }
    }

    void GameScreen::updateCamera()
    {
        if (CharacterActor *hero = gameLogic_->hero()) {
            Vector2 offset = camera_->position() - hero->position();
            offset.clampLength(2.0f);
            camera_->position(hero->position() + offset);
        }
    }

    void GameScreen::drawScene()
    {
        camera_->apply();
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        sceneGraph_->draw();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }

    void GameScreen::drawSceneToFramebuffer()
    {
        framebuffer_->bind();
        glViewport(0, 0, framebuffer_->width(), framebuffer_->height());
        drawScene();
        framebuffer_->unbind();
    }

    void GameScreen::drawFramebufferToScreen()
    {
        glViewport(0, 0, window_->width(), window_->height());
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, double(framebuffer_->width()),
                0.0, double(framebuffer_->height()),
                -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);

        framebuffer_->draw();
    }

    void GameScreen::drawPhysics()
    {
        if (b2World *world = gameLogic_->world()) {
            camera_->apply();

            glColor3ub(0, 255, 0);
            b2Transform transform;
            transform.SetIdentity();
            physicsDraw_->DrawTransform(transform);
            world->SetDebugDraw(physicsDraw_.get());
            world->DrawDebugData();
        }
    }

    std::auto_ptr<Screen> createGameScreen(Window *window, bool supersample)
    {
        return std::auto_ptr<Screen>(new GameScreen(window, supersample));
    }
}
