#include "default_frame_buffer.hpp"

#include "context.hpp"
#include "frame_buffer.hpp"
#include "graphics_resource_base.hpp"
#include "texture.hpp"

#include <stdexcept>
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
                glDeleteFramebuffers(1, &name_);
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

        virtual void bind()
        {
            if (name_ == 0) {
                throw std::runtime_error("Must create frame buffer before binding it.");
            }
            glBindFramebuffer(GL_FRAMEBUFFER, name_);
        }

        virtual void unbind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
            glGenFramebuffers(1, &name_);
            glBindFramebuffer(GL_FRAMEBUFFER, name_);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                   GL_TEXTURE_2D, colorAttachment_->getName(),
                                   0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        
        void destroyImpl()
        {
            glDeleteFramebuffers(1, &name_);
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
