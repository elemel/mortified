#ifndef MORTIFED_SHADER_SOURCE_HPP
#define MORTIFIED_SHADER_SOURCE_HPP

#include <SDL/SDL_opengl.h>

namespace mortified {
    class ShaderSource {
    public:
        virtual ~ShaderSource()
        { }

        virtual bool isValid() const = 0;

        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual GLenum getType() const = 0;
        virtual GLint getSize() const = 0;
        virtual GLchar const *getData() const = 0;
    };
}

#endif
