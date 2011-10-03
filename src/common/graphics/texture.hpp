#ifndef MORTIFIED_TEXTURE_HPP
#define MORTIFIED_TEXTURE_HPP

#include "graphics_resource.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class Context;

    class Texture : public virtual GraphicsResource {
    public:
        virtual int name() const = 0;
        virtual int width() const = 0;
        virtual int height() const = 0;
    };
}

#endif
