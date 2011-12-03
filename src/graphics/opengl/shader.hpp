#ifndef MORTIFIED_SHADER_HPP
#define MORTIFIED_SHADER_HPP

#include "graphics_resource.hpp"

#include <memory>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class ShaderSource;

    class Shader : public virtual GraphicsResource {
    public:
        virtual GLuint getName() const = 0;

        virtual void setSource(std::auto_ptr<ShaderSource> source) = 0;        
    };
}

#endif
