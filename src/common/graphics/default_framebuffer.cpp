#include "default_framebuffer.hpp"

#include "framebuffer.hpp"

#include <cassert>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultFramebuffer :
        public virtual Framebuffer
    {
    public:
        DefaultFramebuffer(int width, int height) :
            width_(width),
            height_(height),
            texture_(0),
            framebuffer_(0)
        {
            create();
        }

        ~DefaultFramebuffer()
        {
            if (framebuffer_) {
                glDeleteFramebuffersEXT(1, &framebuffer_);
                framebuffer_ = 0;
            }
            if (texture_) {
                glDeleteTextures(1, &texture_);
                texture_ = 0;
            }
        }

        int width() const
        {
            return width_;
        }

        int height() const
        {
            return height_;
        }

        void create()
        {
            if (texture_ == 0) {
                glGenTextures(1, &texture_);
                glBindTexture(GL_TEXTURE_2D, texture_);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                                GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                                GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, 4, width_, height_, 0,
                             GL_RGBA, GL_UNSIGNED_BYTE, 0);
            }

            if (framebuffer_ == 0) {
                glGenFramebuffersEXT(1, &framebuffer_);
                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer_);
                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
                                          GL_COLOR_ATTACHMENT0_EXT,
                                          GL_TEXTURE_2D, texture_, 0);
                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            }
        }

        void invalidate()
        {
            texture_ = 0;
            framebuffer_ = 0;
        }

        void bind()
        {
            assert(framebuffer_);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer_);
        }

        void unbind()
        {
            assert(framebuffer_);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        }

        void draw()
        {
            assert(texture_);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_);
            glBegin(GL_QUADS);
            {
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(0.0f, 0.0f);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(float(width_), 0.0f);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(float(width_), float(height_));
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(0.0f, float(height_));
            }
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }

    private:
        int width_;
        int height_;
        GLuint texture_;
        GLuint framebuffer_;
    };

    std::auto_ptr<Framebuffer> createFramebuffer(int width, int height)
    {
        return std::auto_ptr<Framebuffer>(new DefaultFramebuffer(width,
                                                                 height));
    }
}
