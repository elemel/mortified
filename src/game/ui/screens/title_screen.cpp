#include "game_screen.hpp"

#include "default_font.hpp"
#include "default_graphics_manager.hpp"
#include "default_stream.hpp"
#include "default_texture.hpp"
#include "font.hpp"
#include "graphics_manager.hpp"
#include "image.hpp"
#include "screen.hpp"
#include "stream.hpp"
#include "texture.hpp"
#include "window.hpp"

#include <boost/shared_ptr.hpp>

namespace mortified {
    class TitleScreen : public virtual Screen {
    public:
        explicit TitleScreen(Window *window) :
            window_(window),
            graphicsManager_(createGraphicsManager())
        { }

        void create()
        {
            std::auto_ptr<Stream> fontStream =
                createStreamFromFile("../../../content/fonts/linux-biolinum/linux-biolinum-small-caps.ttf", "rb");
            font_ = createFont(fontStream.get(), 256);

            logotypeImage_ = font_->render("mortified");
            logotypeTexture_ = createTexture(logotypeImage_);
            graphicsManager_->addResource(logotypeTexture_);
        }

        void destroy()
        {
            font_.reset();
        }

        bool handleEvent(SDL_Event const *event)
        {
            return false;
        }
        
        void update()
        { }

        void draw()
        {
            int windowWidth = window_->width();
            int windowHeight = window_->height();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, double(windowWidth), double(windowHeight), 0.0, -1.0, 1.0);
            glMatrixMode(GL_MODELVIEW);

            logotypeTexture_->create();

            int logotypeWidth = logotypeTexture_->width();
            int logotypeHeight = logotypeTexture_->height();
            int logotypeX = windowWidth / 2 - logotypeWidth / 2;
            int logotypeY = windowHeight / 2 - logotypeHeight / 2;

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, logotypeTexture_->name());
            glBegin(GL_QUADS);
            {
                glColor3f(1.0f, 0.8f, 0.2f);
                glTexCoord2i(0, 0);
                glVertex2i(logotypeX, logotypeY);
                glTexCoord2i(1, 0);
                glVertex2i(logotypeX + logotypeWidth, logotypeY);
                glTexCoord2i(1, 1);
                glVertex2i(logotypeX + logotypeWidth, logotypeY + logotypeHeight);
                glTexCoord2i(0, 1);
                glVertex2i(logotypeX, logotypeY + logotypeHeight);
            }
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
        }

        void resize(int width, int height)
        {
            graphicsManager_->invalidate();
        }
        
    private:
        Window *window_;
        boost::shared_ptr<GraphicsManager> graphicsManager_;
        boost::shared_ptr<Font> font_;
        boost::shared_ptr<Image> logotypeImage_;
        boost::shared_ptr<Texture> logotypeTexture_;
    };

    std::auto_ptr<Screen> createTitleScreen(Window *window)
    {
        return std::auto_ptr<Screen>(new TitleScreen(window));
    }
}
