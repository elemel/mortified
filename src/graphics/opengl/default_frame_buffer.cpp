#include "default_frame_buffer.hpp"

#include "context.hpp"
#include "frame_buffer.hpp"
#include "graphics_resource_base.hpp"
#include "texture.hpp"

#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultFrameBuffer :
        public virtual FrameBuffer,
        private virtual GraphicsResourceBase
    {
    public:
        explicit DefaultFrameBuffer(boost::intrusive_ptr<Context> context) :
            context_(context),
            name_(0)
        {
            addParent(context_);
        }

        ~DefaultFrameBuffer()
        {
            if (name_) {
                glDeleteFramebuffersEXT(1, &name_);
            }
        }

        void setColorAttachment(boost::intrusive_ptr<Texture> texture)
        {
            if (!colorAttachment_) {
                colorAttachment_ = texture;
                addParent(colorAttachment_);
            }
        }

        bool isValid() const
        {
            return name_ != 0;
        }

        GLuint getName() const
        {
            return name_;
        }

        FrameBuffer *asFrameBuffer()
        {
            return this;
        }

        FrameBuffer const *asFrameBuffer() const
        {
            return this;
        }

    private:
        boost::intrusive_ptr<Context> context_;
        boost::intrusive_ptr<Texture> colorAttachment_;
        GLuint name_;

        void createImpl()
        {
            glGenFramebuffersEXT(1, &name_);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, name_);
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
                                      GL_COLOR_ATTACHMENT0_EXT,
                                      GL_TEXTURE_2D, colorAttachment_->getName(), 0);
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

    boost::intrusive_ptr<FrameBuffer>
    createFrameBuffer(boost::intrusive_ptr<Context> context)
    {
        return boost::intrusive_ptr<FrameBuffer>(new DefaultFrameBuffer(context));
    }
}
