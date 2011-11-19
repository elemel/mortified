#ifndef MORTIFIED_TEXTURE_HPP
#define MORTIFIED_TEXTURE_HPP

#include "graphics_resource.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class Context;
    class Framebuffer;

    class Texture : public virtual GraphicsResource {
    public:
        virtual int getName() const = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual GLenum getMinFilter() const = 0;
        virtual void setMinFilter(GLenum filter) = 0;

        virtual GLenum getMagFilter() const = 0;
        virtual void setMagFilter(GLenum filter) = 0;
    };
}

#endif
