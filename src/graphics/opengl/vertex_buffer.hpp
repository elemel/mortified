#ifndef MORTIFIED_VERTEX_BUFFER_HPP
#define MORTIFIED_VERTEX_BUFFER_HPP

#include "graphics_resource.hpp"

#include <memory>
#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class VertexBufferSource;
    
    class VertexBuffer : public virtual GraphicsResource {
    public:
        virtual GLuint getName() const = 0;

        virtual void setUsage(GLenum usage) = 0;
        
        virtual void setSource(std::auto_ptr<VertexBufferSource> source) = 0;        

        virtual void setMode(GLenum mode) = 0;
        
        virtual void draw() = 0;
    };
}

#endif
