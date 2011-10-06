#include "default_framebuffer.hpp"

#include "framebuffer.hpp"
#include "graphics_object_base.hpp"
#include "texture.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultFramebuffer :
        public virtual Framebuffer,
        private virtual GraphicsObjectBase
    {
    public:
        explicit DefaultFramebuffer(Texture *texture) :
            texture_(texture),
            name_(0)
        {
            addParent(texture);
        }

        ~DefaultFramebuffer()
        {
            if (name_) {
                glDeleteFramebuffersEXT(1, &name_);
            }
        }

        bool exists() const
        {
            return name_ != 0;
        }

        int name() const
        {
            return name_;
        }

        Framebuffer *asFramebuffer()
        {
            return this;
        }

        Framebuffer const *asFramebuffer() const
        {
            return this;
        }

    private:
        Texture *texture_;
        GLuint name_;

        void createImpl()
        {
            glGenFramebuffersEXT(1, &name_);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, name_);
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
                                      GL_COLOR_ATTACHMENT0_EXT,
                                      GL_TEXTURE_2D, texture_->name(), 0);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        }
        
        void destroyImpl()
        {
            glDeleteFramebuffersEXT(1, &name_);
            name_ = 0;
        }
        
        void invalidateImpl()
        {
            name_ = 0;
        }
    };
    
    boost::intrusive_ptr<Framebuffer> createFramebuffer(Texture *texture)
    {
        return new DefaultFramebuffer(texture);
    }
}
