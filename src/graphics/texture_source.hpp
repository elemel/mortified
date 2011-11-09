#ifndef MORTIFIED_TEXTURE_SOURCE_HPP
#define MORTIFIED_TEXTURE_SOURCE_HPP

#include "ref_counted.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class TextureSource : public virtual RefCounted {
    public:
        virtual ~TextureSource()
        { }

        virtual bool exists() const = 0;

        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual void const *getPixels() const = 0;
    };
}

#endif
