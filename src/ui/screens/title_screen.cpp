#include "game_screen.hpp"

#include "context.hpp"
#include "default_font.hpp"
#include "default_image.hpp"
#include "default_texture.hpp"
#include "editor_screen.hpp"
#include "empty_texture_source.hpp"
#include "font.hpp"
#include "framebuffer.hpp"
#include "game_screen.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "screen.hpp"
#include "texture.hpp"
#include "window.hpp"

#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class TitleScreen : public virtual Screen {
    public:
        explicit TitleScreen(Window *window) :
            window_(window),
            angle_(0.0f)
        { }

        void create()
        {
            font_ = loadFontFromFile("../../../data/fonts/teen/teen.ttf", 256);

            logoImage_ = font_->render("Mortified");
            logoImage_->flipVertical();
            logoTexture_ = window_->getContext()->createTexture(createImageTextureSource(logoImage_));
            logoTexture_->setMinFilter(GL_LINEAR);
            logoTexture_->setMagFilter(GL_LINEAR);

            targetTexture_ = window_->getContext()->createTexture(128, 128);
            targetFramebuffer_ = targetTexture_->createFramebuffer();
        }

        void destroy()
        {
            font_.reset();
        }

        bool handleEvent(SDL_Event const *event)
        {
            if (event->type == SDL_KEYDOWN) {
                switch (event->key.keysym.sym) {
                case SDLK_e:
                    window_->addScreen(createEditorScreen(window_));
                    return true;

                case SDLK_g:
                case SDLK_SPACE:
                    window_->addScreen(createGameScreen(window_, true));
                    return true;

                case SDLK_q:
                    window_->removeScreen(this);
                    return true;
                }
            }
            return false;
        }
        
        void update()
        {
            float time = 0.001f * SDL_GetTicks();
            angle_ = 3.0f * time + 0.5f * std::sin(5.0f * time);
        }

        void draw()
        {
            drawLogoToTarget();
            drawTargetToScreen();
        }
        
    private:
        Window *window_;
        boost::intrusive_ptr<Font> font_;
        boost::intrusive_ptr<Image> logoImage_;
        boost::intrusive_ptr<Texture> logoTexture_;
        boost::intrusive_ptr<Texture> targetTexture_;
        boost::intrusive_ptr<Framebuffer> targetFramebuffer_;
        float angle_;

        void drawLogoToTarget()
        {
            logoTexture_->create();
            targetFramebuffer_->create();
            
            glViewport(0, 0, targetTexture_->getWidth(),
                       targetTexture_->getHeight());
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            
            float aspectRatio = (float(logoTexture_->getWidth()) /
                                 float(logoTexture_->getHeight()));
            float scale = 0.2f;
            
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,
                                 targetFramebuffer_->getName());
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, logoTexture_->getName());
            glPushMatrix();
            glRotatef(angle_, 0.0f, 0.0f, 1.0f);
            glColor3f(1.0f, 0.8f, 0.2f);
            glBegin(GL_QUADS);
            {
                glTexCoord2i(0, 0);
                glVertex2f(-scale * aspectRatio, -scale);
                glTexCoord2i(1, 0);
                glVertex2f(scale * aspectRatio, -scale);
                glTexCoord2i(1, 1);
                glVertex2f(scale * aspectRatio, scale);
                glTexCoord2i(0, 1);
                glVertex2f(-scale * aspectRatio, scale);
            }
            glEnd();
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        }
        
        void drawTargetToScreen()
        {
            float aspectRatio = (float(window_->getWidth()) /
                                 float(window_->getHeight()));
            float scale = 1.5f;
            
            glViewport(0, 0, window_->getWidth(), window_->getHeight());
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-aspectRatio, aspectRatio, -1.0, 1.0, -1.0, 1.0);
            glMatrixMode(GL_MODELVIEW);
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, targetTexture_->getName());
            glPushMatrix();
            glRotatef(-angle_, 0.0f, 0.0f, 1.0f);
            glBegin(GL_QUADS);
            {
                glTexCoord2i(0, 0);
                glVertex2f(-scale, -scale);
                glTexCoord2i(1, 0);
                glVertex2f(scale, -scale);
                glTexCoord2i(1, 1);
                glVertex2f(scale, scale);
                glTexCoord2i(0, 1);
                glVertex2f(-scale, scale);
            }
            glEnd();
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
        }
    };

    std::auto_ptr<Screen> createTitleScreen(Window *window)
    {
        return std::auto_ptr<Screen>(new TitleScreen(window));
    }
}
