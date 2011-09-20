#ifndef MORTIFIED_TEXTURE_SOURCE_HPP
#define MORTIFIED_TEXTURE_SOURCE_HPP

#include <SDL/SDL_opengl.h>

namespace mortified {
    class TextureSource {
    public:
        virtual GLsizei width() const = 0;
        virtual GLsizei height() const = 0;
        virtual GLvoid const *pixels() const = 0;
    };
}

#endif
