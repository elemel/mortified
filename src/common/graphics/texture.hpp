#ifndef MORTIFIED_TEXTURE_HPP
#define MORTIFIED_TEXTURE_HPP

#include "graphics_object.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class Context;
    class Framebuffer;

    class Texture : public virtual GraphicsObject {
    public:
        virtual int name() const = 0;
        virtual int width() const = 0;
        virtual int height() const = 0;

        virtual GLenum minFilter() const = 0;
        virtual void minFilter(GLenum filter) = 0;

        virtual GLenum magFilter() const = 0;
        virtual void magFilter(GLenum filter) = 0;

        virtual boost::shared_ptr<Framebuffer> createFramebuffer() = 0;
    };
}

#endif
