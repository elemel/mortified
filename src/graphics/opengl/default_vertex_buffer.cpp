#include "default_vertex_buffer.hpp"

#include "context.hpp"
#include "graphics_resource_base.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_source.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultVertexBuffer :
        public virtual VertexBuffer,
        private virtual GraphicsResourceBase
    {
    public:
        explicit DefaultVertexBuffer(boost::intrusive_ptr<Context> context) :
            name_(0),
            usage_(GL_STATIC_DRAW),
            mode_(GL_TRIANGLES),
            count_(0),
            vertexSize_(0),
            texCoordSize_(0),
            colorSize_(0)
        {
            addParent(context);
        }

        ~DefaultVertexBuffer()
        {
            if (name_) {
                glDeleteBuffersARB(1, &name_);
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

        void setUsage(GLenum usage)
        {
            usage_ = usage;
        }
        
        void setSource(boost::intrusive_ptr<VertexBufferSource> source)
        {
            source_ = source;
        }
        
        void setMode(GLenum mode)
        {
            mode_ = mode;
        }
        
        void draw()
        {
            glBindBufferARB(GL_ARRAY_BUFFER, name_);
            if (vertexSize_) {
                glEnableClientState(GL_VERTEX_ARRAY);
            }
            if (texCoordSize_) {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            if (colorSize_) {
                glEnableClientState(GL_COLOR_ARRAY);
            }
            glDrawArrays(mode_, 0, count_);
            if (colorSize_) {
                glDisableClientState(GL_COLOR_ARRAY);
            }
            if (texCoordSize_) {
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            if (vertexSize_) {
                glDisableClientState(GL_VERTEX_ARRAY);
            }
            glBindBufferARB(GL_ARRAY_BUFFER, 0);
        }

        VertexBuffer *asVertexBuffer()
        {
            return this;
        }
        
        VertexBuffer const *asVertexBuffer() const
        {
            return this;
        }
        
    private:
        GLuint name_;
        GLenum usage_;
        GLenum mode_;
        boost::intrusive_ptr<VertexBufferSource> source_;
        GLsizei count_;
        GLsizei vertexSize_;
        GLsizei texCoordSize_;
        GLsizei colorSize_;

        void createImpl()
        {
            glGenBuffersARB(1, &name_);
            if (source_) {
                source_->create();

                GLsizei stride = source_->getStride();
                count_ = source_->getCount();
                vertexSize_ = source_->getVertexSize();
                texCoordSize_ = source_->getTexCoordSize();
                colorSize_ = source_->getColorSize();

                glBindBufferARB(GL_ARRAY_BUFFER, name_);
                glBufferDataARB(GL_ARRAY_BUFFER, stride * count_,
                                source_->getData(), usage_);
                if (vertexSize_) {
                    glVertexPointer(vertexSize_, source_->getVertexType(),
                                    stride, source_->getVertexOffset());
                }
                if (texCoordSize_) {
                    glTexCoordPointer(texCoordSize_,
                                      source_->getTexCoordType(), stride,
                                      source_->getTexCoordOffset());
                }
                if (colorSize_) {
                    glColorPointer(colorSize_, source_->getColorType(),
                                   stride, source_->getColorOffset());
                }
                glBindBufferARB(GL_ARRAY_BUFFER, 0);
            }
        }
        
        void destroyImpl()
        {
            glDeleteBuffersARB(1, &name_);
            name_ = 0;
        }

        void invalidateImpl()
        {
            name_ = 0;
        }
    };

    boost::intrusive_ptr<VertexBuffer>
    createVertexBuffer(boost::intrusive_ptr<Context> context)
    {
        return boost::intrusive_ptr<VertexBuffer>(new DefaultVertexBuffer(context));
    }
}
