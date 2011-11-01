#ifndef MORTIFIED_TEXTURE_SOURCE_HPP
#define MORTIFIED_TEXTURE_SOURCE_HPP

#include <SDL/SDL_opengl.h>

namespace mortified {
    class TextureSource {
    public:
        virtual bool exists() const = 0;

        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual int width() const = 0;
        virtual int height() const = 0;

        virtual void const *pixels() const = 0;
    };
}

#endif