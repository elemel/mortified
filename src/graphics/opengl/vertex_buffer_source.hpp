#ifndef MORTIFIED_VERTEX_BUFFER_SOURCE_HPP
#define MORTIFIED_VERTEX_BUFFER_SOURCE_HPP

#include "ref_counted.hpp"

namespace mortified {
    class VertexBufferSource : public virtual RefCounted {
    public:
        virtual bool isValid() const = 0;
        
        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual GLsizei getStride() const = 0;
        virtual GLsizei getCount() const = 0;
        virtual GLvoid const *getData() const = 0;

        virtual GLint getVertexCoordCount() const = 0;
        virtual GLenum getVertexCoordType() const = 0;
        virtual GLvoid const *getVertexCoordOffset() const = 0;

        virtual GLint getTextureCoordCount() const = 0;
        virtual GLenum getTextureCoordType() const = 0;
        virtual GLvoid const *getTextureCoordOffset() const = 0;

        virtual GLint getColorCompCount() const = 0;
        virtual GLenum getColorCompType() const = 0;
        virtual GLvoid const *getColorCompOffset() const = 0;
    };
}

#endif
