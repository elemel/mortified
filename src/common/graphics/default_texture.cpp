#include "default_texture.hpp"

#include "image.hpp"
#include "math.hpp"
#include "texture.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <SDL/SDL_image.h>

namespace mortified {
    class DefaultTexture :
        public virtual Texture
    {
    public:
        DefaultTexture() :
            name_(0)
        { }

        ~DefaultTexture()
        {
            glDeleteTextures(1, &name_);
        }

        void create(Image const *image)
        {
            assert(image);
            destroy();

            ImageSize imageSize = image->size();
            size_ = TextureSize(imageSize.width, imageSize.height);

            glGenTextures(1, &name_);
            glBindTexture(GL_TEXTURE_2D, name_);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, 4, size_.width, size_.height, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, image->data());
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void destroy()
        {
            if (name_) {
                glDeleteTextures(1, &name_);
                name_ = 0;
                size_ = TextureSize();
            }
        }

        void invalidate()
        {
            name_ = 0;
            size_ = TextureSize();
        }

        GLenum target() const
        {
            return GL_TEXTURE_2D;
        }

        GLuint name() const
        {
            return name_;
        }

        TextureSize size() const
        {
            return size_;
        }

        void bind()
        {
            assert(name_);
            glBindTexture(GL_TEXTURE_2D, name_);
        }

        void unbind()
        {
            assert(name_);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

    private:
        GLuint name_;
        TextureSize size_;
    };

    std::auto_ptr<Texture> createTexture()
    {
        return std::auto_ptr<Texture>(new DefaultTexture);
    }

    std::auto_ptr<Texture> createTexture(Image const *image)
    {
        std::auto_ptr<Texture> texture = createTexture();
        texture->create(image);
        return texture;
    }
}
