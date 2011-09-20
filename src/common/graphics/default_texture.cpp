#include "default_texture.hpp"

#include "texture.hpp"
#include "texture_source.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultTexture : public virtual Texture {
    public:
        DefaultTexture(boost::shared_ptr<TextureSource const> source) :
            source_(source),
            name_(0),
            width_(0),
            height_(0),
            minFilter_(GL_NEAREST),
            magFilter_(GL_NEAREST)
        { }

        ~DefaultTexture()
        {
            if (name_) {
                glDeleteTextures(1, &name_);
            }
        }

        bool valid() const
        {
            return name_ != 0;
        }

        void create()
        {
            if (name_ == 0) {
                glGenTextures(1, &name_);
                glBindTexture(GL_TEXTURE_2D, name_);
                width_ = source_->width();
                height_ = source_->height();
                glTexImage2D(GL_TEXTURE_2D, 0, 4, width_, height_, 0,
                             GL_RGBA, GL_UNSIGNED_BYTE, source_->pixels());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter_);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter_);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

        void destroy()
        {
            if (name_) {
                glDeleteTextures(1, &name_);
                name_ = 0;
            }
        }

        void invalidate()
        {
            name_ = 0;
        }

        int name() const
        {
            return name_;
        }

        int width() const
        {
            return width_;
        }

        int height() const
        {
            return height_;
        }

    private:
        boost::shared_ptr<TextureSource const> source_;
        GLuint name_;
        GLsizei width_;
        GLsizei height_;
        GLenum minFilter_;
        GLenum magFilter_;
    };

    boost::shared_ptr<Texture> createTexture(boost::shared_ptr<TextureSource const> source)
    {
        return boost::shared_ptr<Texture>(new DefaultTexture(source));
    }
}
