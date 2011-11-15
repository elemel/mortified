
#include "game_screen.hpp"

#include "context.hpp"
#include "default_game.hpp"
#include "default_actor.hpp"
#include "default_image.hpp"
#include "default_stream.hpp"
#include "empty_texture_source.hpp"
#include "framebuffer.hpp"
#include "game.hpp"
#include "graphics_service.hpp"
#include "actor.hpp"
#include "graphics_service.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "math.hpp"
#include "physics_draw.hpp"
#include "physics_component.hpp"
#include "physics_service.hpp"
#include "property_component.hpp"
#include "scene.hpp"
#include "screen.hpp"
#include "stream.hpp"
#include "texture.hpp"
#include "window.hpp"
#include "xml.hpp"

#include <memory>
#include <iostream>
#include <stdexcept>
#include <Box2D/Box2D.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class GameScreen : public virtual Screen {
    public:
        GameScreen(Window *window, bool supersample) :
            window_(window),
            updateTime_(0.0f),
            dt_(1.0f / 60.0f),
            supersample_(supersample),
            cameraScale_(7.0f)
        { }
        
        void create()
        {
            physicsDraw_ = createPhysicsDraw();
            game_ = createGame(window_->getContext());
            loadConfig("../../../data/configs/config.xml");
            game_->loadModule("../../../data/modules/level.xml", Matrix3());
        }
        
        void destroy()
        {
            game_->saveModule("../../../data/modules/save.xml", Matrix3());
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
            updateInput();
            updateGame(time);
            updateCamera();
        }
        
        void draw()
        {
            if (supersample_) {
                drawSceneToTarget();
                drawTargetToScreen();
            } else {
                drawScene();
            }
            // drawPhysics();
        }
        
    private:
        Window *window_;
        float updateTime_;
        float dt_;
        std::auto_ptr<Game> game_;
        std::auto_ptr<b2Draw> physicsDraw_;
        Vector2 cameraPosition_;
        float cameraScale_;

        bool supersample_;
        boost::intrusive_ptr<Texture> targetTexture_;
        boost::intrusive_ptr<Framebuffer> targetFramebuffer_;

        void loadConfig(char const *file)
        {
            std::auto_ptr<Stream> stream = createStreamFromFile(file, "rb");
            
            int size = stream->seek(0, RW_SEEK_END);
            stream->seek(0, RW_SEEK_SET);
            std::vector<char> buffer(size + 1);
            stream->read(&buffer[0], size);
            buffer.back() = 0;
            
            rapidxml::xml_document<> document;
            document.parse<0>(&buffer[0]);
            for (rapidxml::xml_node<> *child = document.first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element &&
                    strcmp(child->name(), "config") == 0)
                {
                    loadConfig(child);
                }
            }
        }

        void loadConfig(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (strcmp(child->name(), "game-screen") == 0) {
                        loadGameScreenConfig(child);
                    }
                }
            }
        }
        
        void loadGameScreenConfig(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (strcmp(child->name(), "game") == 0) {
                        game_->loadConfig(child);
                    }
                }
            }
        }

        void skipFrames(float time)
        {
            if (time - updateTime_ >= 10.0f * dt_) {
                int skip = int((time - updateTime_) / dt_);
                updateTime_ += float(skip) * dt_;
                std::cerr << "WARNING: Skipped " << skip << " frame(s)." << std::endl;
            }
            assert(time - updateTime_ <= 10.0f * dt_);
        }

        void updateInput()
        {
            Actor *actor = game_->findActor("wizard");
            if (actor) {
                PropertyComponent *component = actor->getPropertyComponent();
                if (component) {
                    bool *upInput = component->findBool("up-input");
                    bool *leftInput = component->findBool("left-input");
                    bool *downInput = component->findBool("down-input");
                    bool *rightInput = component->findBool("right-input");
                    bool *jumpInput = component->findBool("jump-input");

                    Uint8 *state = SDL_GetKeyboardState(0);
                    if (upInput) {
                        *upInput = bool(state[SDL_SCANCODE_W]) | bool(state[SDL_SCANCODE_UP]);
                    }
                    if (leftInput) {
                        *leftInput = bool(state[SDL_SCANCODE_A]) | bool(state[SDL_SCANCODE_LEFT]);
                    }
                    if (downInput) {
                        *downInput = bool(state[SDL_SCANCODE_S]) | bool(state[SDL_SCANCODE_DOWN]);
                    }
                    if (rightInput) {
                        *rightInput = bool(state[SDL_SCANCODE_D]) | bool(state[SDL_SCANCODE_RIGHT]);
                    }
                    if (jumpInput) {
                        *jumpInput = bool(state[SDL_SCANCODE_SPACE]);
                    }
                }
            }
        }

        void updateGame(float time)
        {
            while (time - updateTime_ >= dt_) {
                updateTime_ += dt_;
                game_->update(dt_);
            }
        }

        void updateCamera()
        {
            Actor *actor = game_->findActor("wizard");
            if (actor) {
                PhysicsComponent *component = actor->getPhysicsComponent();
                if (component) {
                    b2Body *bodyBody = component->findBody("body");
                    if (bodyBody) {
                        b2Vec2 position = bodyBody->GetPosition();
                        cameraPosition_.x = position.x;
                        cameraPosition_.y = position.y;
                    }
                }
            }
        }

        void drawScene()
        {
            applyCamera();
            glClear(GL_COLOR_BUFFER_BIT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            game_->getGraphicsService()->getScene()->draw();
            glDisable(GL_BLEND);
        }
        
        void drawSceneToTarget()
        {
            if (!targetTexture_ ||
                targetTexture_->getWidth() != 2 * window_->getWidth() ||
                targetTexture_->getHeight() != 2 * window_->getHeight())
            {
                targetTexture_ = window_->getContext()->createTexture(2 * window_->getWidth(),
                                                                      2 * window_->getHeight());
                targetTexture_->setMinFilter(GL_LINEAR);
                targetTexture_->setMagFilter(GL_LINEAR);
                targetFramebuffer_ = targetTexture_->createFramebuffer();
            }
            
            targetFramebuffer_->create();

            glViewport(0, 0, window_->getWidth() * 2,
                       window_->getHeight() * 2);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,
                                 targetFramebuffer_->getName());
            glClearColor(0.0, 0.0, 0.0, 0.0);
            drawScene();
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            glViewport(0, 0, window_->getWidth(), window_->getHeight());
        }
        
        void drawTargetToScreen()
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, double(window_->getWidth() * 2),
                    0.0, double(window_->getHeight() * 2),
                    -1.0, 1.0);
            glMatrixMode(GL_MODELVIEW);
            
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, targetTexture_->getName());
            glColor3ub(255, 255, 255);
            glBegin(GL_QUADS);
            {
                glTexCoord2i(0, 0);
                glVertex2i(0, 0);
                glTexCoord2i(1, 0);
                glVertex2i(window_->getWidth() * 2, 0);
                glTexCoord2i(1, 1);
                glVertex2i(window_->getWidth() * 2, window_->getHeight() * 2);
                glTexCoord2i(0, 1);
                glVertex2i(0, window_->getHeight() * 2);
            }
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }
        
        void drawPhysics()
        {
            applyCamera();
            glColor3ub(0, 255, 0);
            b2Transform transform;
            transform.SetIdentity();
            physicsDraw_->DrawTransform(transform);
            b2World *world = game_->getPhysicsService()->getWorld();
            world->SetDebugDraw(physicsDraw_.get());
            world->DrawDebugData();
        }

        void applyCamera()
        {
            float aspectRatio = (float(window_->getWidth()) /
                                 float(window_->getHeight()));

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
