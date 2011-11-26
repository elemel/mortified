#ifndef MORTIFIED_VERTEX_BUFFER_SOURCE_HPP
#define MORTIFIED_VERTEX_BUFFER_SOURCE_HPP

#include <SDL/SDL_opengl.h>

namespace mortified {
    class VertexBufferSource {
    public:
        virtual ~VertexBufferSource()
        { }

        virtual bool isValid() const = 0;
        
        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual GLsizei getStride() const = 0;
        virtual GLsizei getCount() const = 0;
        virtual GLvoid const *getData() const = 0;

        virtual GLint getVertexSize() const = 0;
        virtual GLenum getVertexType() const = 0;
        virtual GLvoid const *getVertexOffset() const = 0;

        virtual GLint getTexCoordSize() const = 0;
        virtual GLenum getTexCoordType() const = 0;
        virtual GLvoid const *getTexCoordOffset() const = 0;

        virtual GLint getColorSize() const = 0;
        virtual GLenum getColorType() const = 0;
        virtual GLvoid const *getColorOffset() const = 0;
    };
}

#endif
