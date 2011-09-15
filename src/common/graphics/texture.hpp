#ifndef MORTIFIED_TEXTURE_HPP
#define MORTIFIED_TEXTURE_HPP

#include <SDL/SDL_opengl.h>

namespace mortified {
    class Image;

    class TextureSize {
    public:
        int width;
        int height;

        explicit TextureSize(int size = 0) :
            width(size),
            height(size)
        { }

        TextureSize(int width, int height) :
            width(width),
            height(height)
        { }
    };

    class Texture {
    public:
        virtual ~Texture()
        { }

        virtual void create(Image const *image) = 0;
        virtual void destroy() = 0;
        virtual void invalidate() = 0;

        virtual GLenum target() const = 0;
        virtual GLuint name() const = 0;

        virtual TextureSize size() const = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}

#endif
