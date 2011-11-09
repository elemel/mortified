#include "default_texture.hpp"

#include "context.hpp"
#include "framebuffer.hpp"
#include "default_framebuffer.hpp"
#include "graphics_resource_base.hpp"
#include "texture.hpp"
#include "texture_source.hpp"

#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultTexture :
        public virtual Texture,
        private virtual GraphicsResourceBase
    {
    public:
        DefaultTexture(boost::intrusive_ptr<Context> context,
                       boost::intrusive_ptr<TextureSource> source) :
            source_(source),
            name_(0),
            width_(0),
            height_(0),
            minFilter_(GL_NEAREST),
            magFilter_(GL_NEAREST)
        {
            if (context) {
                addParent(context);
            }
        }

        DefaultTexture(boost::intrusive_ptr<Context> context, int width,
                       int height) :
            name_(0),
            width_(width),
            height_(height),
            minFilter_(GL_NEAREST),
            magFilter_(GL_NEAREST)
        {
            if (context) {
                addParent(context);
            }
        }

        ~DefaultTexture()
        {
            if (name_) {
                glDeleteTextures(1, &name_);
            }
        }

        bool exists() const
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

        int getName() const
        {
            return name_;
        }

        int getWidth() const
        {
            return width_;
        }

        int getHeight() const
        {
            return height_;
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

        boost::intrusive_ptr<Framebuffer> createFramebuffer()
        {
            return mortified::createFramebuffer(this);
        }

    private:
        boost::intrusive_ptr<TextureSource> source_;
        GLuint name_;
        GLsizei width_;
        GLsizei height_;
        GLenum minFilter_;
        GLenum magFilter_;

        void createImpl()
        {
            if (source_) {
                source_->create();

                width_ = source_->getWidth();
                height_ = source_->getHeight();
            }

            glGenTextures(1, &name_);
            glBindTexture(GL_TEXTURE_2D, name_);
            glTexImage2D(GL_TEXTURE_2D, 0, 4, width_, height_, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE,
                         source_ ? source_->getPixels() : 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter_);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter_);
            glBindTexture(GL_TEXTURE_2D, 0);
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
    createTexture(boost::intrusive_ptr<Context> context,
                  boost::intrusive_ptr<TextureSource> source)
    {
        return boost::intrusive_ptr<Texture>(new DefaultTexture(context, source));
    }

    boost::intrusive_ptr<Texture>
    createTexture(boost::intrusive_ptr<Context> context, int width, int height)
    {
        return boost::intrusive_ptr<Texture>(new DefaultTexture(context, width,
                                                                height));
    }
}
