
#include "game_screen.hpp"

#include "actor.hpp"
#include "character_actor.hpp"
#include "character_sprite_controller.hpp"
#include "context.hpp"
#include "default_character_actor.hpp"
#include "default_game_logic.hpp"
#include "default_image.hpp"
#include "default_scene_graph.hpp"
#include "empty_texture_source.hpp"
#include "framebuffer.hpp"
#include "game_logic.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "math.hpp"
#include "physics_draw.hpp"
#include "platform_actor.hpp"
#include "scene_graph.hpp"
#include "screen.hpp"
#include "sprite_controller.hpp"
#include "texture.hpp"
#include "window.hpp"

#include <memory>
#include <iostream>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include <Box2D/Box2D.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class GameScreen :
        public virtual Screen
    {
    public:
        GameScreen(Window *window, bool supersample) :
            window_(window),
            updateTime_(0.0f),
            dt_(1.0f / 60.0f),
            supersample_(supersample),
            cameraScale_(5.0f)
        { }
        
        void create()
        {
            gameLogic_ = createGameLogic();
            physicsDraw_.reset(new PhysicsDraw);
            sceneGraph_ = createSceneGraph();
            
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
        }
        
        void destroy()
        {
            targetFramebuffer_.reset();
            targetTexture_.reset();
        }
        
        bool handleEvent(SDL_Event const *event)
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
        
        void update()
        {
            float time = 0.001f * SDL_GetTicks();
            skipFrames(time);
            updateControls();
            updateGame(time);
            sceneGraph_->update();
        }
        
        void draw()
        {
            updateCamera();
            if (supersample_) {
                drawSceneToTarget();
                drawTargetToScreen();
            } else {
                drawScene();
            }
            drawPhysics();
        }
        
    private:
        Window *window_;
        float updateTime_;
        float dt_;
        std::auto_ptr<GameLogic> gameLogic_;
        std::auto_ptr<b2Draw> physicsDraw_;
        std::auto_ptr<SceneGraph> sceneGraph_;
        Vector2 cameraPosition_;
        float cameraScale_;

        bool supersample_;
        boost::shared_ptr<Texture> targetTexture_;
        boost::shared_ptr<Framebuffer> targetFramebuffer_;

        void skipFrames(float time)
        {
            if (time - updateTime_ >= 10.0f * dt_) {
                int skip = int((time - updateTime_) / dt_);
                updateTime_ += float(skip) * dt_;
                std::cerr << "WARNING: Skipped " << skip << " frame(s)." << std::endl;
            }
            assert(time - updateTime_ <= 10.0f * dt_);
        }
        
        void updateControls()
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
        
        void updateGame(float time)
        {
            while (time - updateTime_ >= dt_) {
                updateTime_ += dt_;
                gameLogic_->update(dt_);
            }
        }
        
        void updateCamera()
        {
            if (CharacterActor *hero = gameLogic_->hero()) {
                Vector2 offset = cameraPosition_ - hero->position();
                offset.clampLength(2.0f);
                cameraPosition_ = hero->position() + offset;
            }
        }
        
        void drawScene()
        {
            applyCamera();

            glClear(GL_COLOR_BUFFER_BIT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
            sceneGraph_->draw();
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
        }
        
        void drawSceneToTarget()
        {
            if (!targetTexture_ ||
                targetTexture_->width() != 2 * window_->width() ||
                targetTexture_->height() != 2 * window_->height())
            {
                targetTexture_ = window_->context()->createTexture(2 * window_->width(),
                                                                   2 * window_->height());
                targetTexture_->minFilter(GL_LINEAR);
                targetTexture_->magFilter(GL_LINEAR);
                targetFramebuffer_ = targetTexture_->createFramebuffer();
            }
            
            targetFramebuffer_->create();

            glViewport(0, 0, window_->width() * 2, window_->height() * 2);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,
                                 targetFramebuffer_->name());
            glClearColor(0.0, 0.0, 0.0, 0.0);
            drawScene();
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            glViewport(0, 0, window_->width(), window_->height());
        }
        
        void drawTargetToScreen()
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, double(window_->width() * 2),
                    0.0, double(window_->height() * 2),
                    -1.0, 1.0);
            glMatrixMode(GL_MODELVIEW);
            
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, targetTexture_->name());
            glBegin(GL_QUADS);
            {
                glTexCoord2i(0, 0);
                glVertex2i(0, 0);
                glTexCoord2i(1, 0);
                glVertex2i(window_->width() * 2, 0);
                glTexCoord2i(1, 1);
                glVertex2i(window_->width() * 2, window_->height() * 2);
                glTexCoord2i(0, 1);
                glVertex2i(0, window_->height() * 2);
            }
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }
        
        void drawPhysics()
        {
            if (b2World *world = gameLogic_->world()) {
                applyCamera();
                
                glColor3ub(0, 255, 0);
                b2Transform transform;
                transform.SetIdentity();
                physicsDraw_->DrawTransform(transform);
                world->SetDebugDraw(physicsDraw_.get());
                world->DrawDebugData();
            }
        }

        void applyCamera()
        {
            float aspectRatio = (float(window_->width()) /
                                 float(window_->height()));

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(cameraPosition_.x - cameraScale_ * aspectRatio,
                    cameraPosition_.x + cameraScale_ * aspectRatio,
                    cameraPosition_.y - cameraScale_,
                    cameraPosition_.y + cameraScale_, -1.0f, 1.0f);
            glMatrixMode(GL_MODELVIEW);
        }
    };

    std::auto_ptr<Screen> createGameScreen(Window *window, bool supersample)
    {
        return std::auto_ptr<Screen>(new GameScreen(window, supersample));
    }
}
