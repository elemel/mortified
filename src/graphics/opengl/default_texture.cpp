#include "default_texture.hpp"

#include "context.hpp"
#include "graphics_resource_base.hpp"
#include "texture.hpp"
#include "texture_source.hpp"

#include <stdexcept>
#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultTexture :
        public virtual Texture,
        private virtual GraphicsResourceBase
    {
    public:
        explicit DefaultTexture(boost::intrusive_ptr<Context> context) :
            name_(0),
            width_(0),
            height_(0),
            minFilter_(GL_NEAREST),
            magFilter_(GL_NEAREST)
        {
            addParent(context);
        }

        ~DefaultTexture()
        {
            if (name_) {
                glDeleteTextures(1, &name_);
            }
        }

        bool isValid() const
        {
            return name_ != 0;
        }

        Texture *asTexture()
        {
            return this;
        }
        
        Texture const *asTexture() const
        {
            return this;
        }

        GLuint getName() const
        {
            return name_;
        }

        GLsizei getWidth() const
        {
            return width_;
        }

        GLsizei getHeight() const
        {
            return height_;
        }

        void setSize(GLsizei width, GLsizei height)
        {
            width_ = width;
            height_ = height;
        }
        
        void setSource(std::auto_ptr<TextureSource> source)
        {
            source_ = source;
        }

        GLenum getMinFilter() const
        {
            return minFilter_;
        }

        void setMinFilter(GLenum filter)
        {
            minFilter_ = filter;
        }
        
        GLenum getMagFilter() const
        {
            return magFilter_;
        }

        void setMagFilter(GLenum filter)
        {
            magFilter_ = filter;
        }

        void bind()
        {
            if (name_ == 0) {
                throw std::runtime_error("Must create texture before binding it.");
            }
            glBindTexture(GL_TEXTURE_2D, name_);
        }

        void unbind()
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

    private:
        std::auto_ptr<TextureSource> source_;
        GLuint name_;
        GLsizei width_;
        GLsizei height_;
        GLenum minFilter_;
        GLenum magFilter_;

        void createImpl()
        {
            if (source_.get()) {
                source_->create();

                width_ = source_->getWidth();
                height_ = source_->getHeight();
            }

            glGenTextures(1, &name_);
            glBindTexture(GL_TEXTURE_2D, name_);
            glTexImage2D(GL_TEXTURE_2D, 0, 4, width_, height_, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE,
                         source_.get() ? source_->getData() : 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter_);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter_);
            glBindTexture(GL_TEXTURE_2D, 0);

            if (source_.get()) {
                source_->destroy();
            }
        }
        
        void destroyImpl()
        {
            glDeleteTextures(1, &name_);
            name_ = 0;
        }
        
        void invalidateImpl()
        {
            name_ = 0;
        }
    };

    boost::intrusive_ptr<Texture>
    createTexture(boost::intrusive_ptr<Context> context)
    {
        return boost::intrusive_ptr<Texture>(new DefaultTexture(context));
    }
}
