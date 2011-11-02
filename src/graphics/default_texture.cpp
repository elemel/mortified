#include "default_texture.hpp"

#include "context.hpp"
#include "framebuffer.hpp"
#include "default_framebuffer.hpp"
#include "graphics_resource_base.hpp"
#include "texture.hpp"
#include "texture_source.hpp"

#include <boost/enable_shared_from_this.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultTexture :
        public virtual Texture,
        public virtual boost::enable_shared_from_this<DefaultTexture>,
        private virtual GraphicsResourceBase
    {
    public:
        DefaultTexture(boost::shared_ptr<Context> context,
                       boost::shared_ptr<TextureSource> source) :
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

        DefaultTexture(boost::shared_ptr<Context> context, int width,
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

        GLenum minFilter() const
        {
            return minFilter_;
        }

        void minFilter(GLenum filter)
        {
            minFilter_ = filter;
        }
        
        GLenum magFilter() const
        {
            return magFilter_;
        }

        void magFilter(GLenum filter)
        {
            magFilter_ = filter;
        }

        boost::shared_ptr<Framebuffer> createFramebuffer()
        {
            return mortified::createFramebuffer(shared_from_this());
        }

    private:
        boost::shared_ptr<TextureSource> source_;
        GLuint name_;
        GLsizei width_;
        GLsizei height_;
        GLenum minFilter_;
        GLenum magFilter_;

        void createImpl()
        {
            if (source_) {
                source_->create();

                width_ = source_->width();
                height_ = source_->height();
            }

            glGenTextures(1, &name_);
            glBindTexture(GL_TEXTURE_2D, name_);
            glTexImage2D(GL_TEXTURE_2D, 0, 4, width_, height_, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE,
                         source_ ? source_->pixels() : 0);
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

    boost::shared_ptr<Texture>
    createTexture(boost::shared_ptr<Context> context,
                  boost::shared_ptr<TextureSource> source)
    {
        return boost::shared_ptr<Texture>(new DefaultTexture(context, source));
    }

    boost::shared_ptr<Texture>
    createTexture(boost::shared_ptr<Context> context, int width, int height)
    {
        return boost::shared_ptr<Texture>(new DefaultTexture(context, width,
                                                             height));
    }
}
