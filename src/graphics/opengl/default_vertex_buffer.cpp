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
            vertexCoordCount_(0),
            textureCoordCount_(0),
            colorCompCount_(0)
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
            if (vertexCoordCount_) {
                glEnableClientState(GL_VERTEX_ARRAY);
            }
            if (textureCoordCount_) {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            if (colorCompCount_) {
                glEnableClientState(GL_COLOR_ARRAY);
            }
            glDrawArrays(mode_, 0, count_);
            if (colorCompCount_) {
                glDisableClientState(GL_COLOR_ARRAY);
            }
            if (textureCoordCount_) {
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            if (vertexCoordCount_) {
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
        GLsizei vertexCoordCount_;
        GLsizei textureCoordCount_;
        GLsizei colorCompCount_;

        void createImpl()
        {
            glGenBuffersARB(1, &name_);
            if (source_) {
                source_->create();

                count_ = source_->getCount();
                vertexCoordCount_ = source_->getVertexCoordCount();
                textureCoordCount_ = source_->getTextureCoordCount();
                colorCompCount_ = source_->getColorCompCount();

                glBindBufferARB(GL_ARRAY_BUFFER, name_);
                glBufferDataARB(GL_ARRAY_BUFFER,
                                source_->getStride() * source_->getCount(),
                                source_->getData(), usage_);
                if (vertexCoordCount_) {
                    glVertexPointer(source_->getVertexCoordCount(),
                                    source_->getVertexCoordType(),
                                    source_->getStride(),
                                    source_->getVertexCoordOffset());
                }
                if (textureCoordCount_) {
                    glTexCoordPointer(source_->getTextureCoordCount(),
                                      source_->getTextureCoordType(),
                                      source_->getStride(),
                                      source_->getTextureCoordOffset());
                }
                if (colorCompCount_) {
                    glColorPointer(source_->getColorCompCount(),
                                   source_->getColorCompType(),
                                   source_->getStride(),
                                   source_->getColorCompOffset());
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
