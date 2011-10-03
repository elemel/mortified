#include "default_image.hpp"

#include "image.hpp"
#include "stream.hpp"

#include <SDL/SDL_image.h>

#include <cassert>
#include <iostream>
#include <stdexcept>

namespace mortified {
    class DefaultImage :
        public virtual Image
    {
    public:
        explicit DefaultImage(SDL_Surface *surface) :
            surface_(surface)
        {
            assert(surface);
            assert(!SDL_MUSTLOCK(surface));
        }

        ~DefaultImage()
        {
            SDL_FreeSurface(surface_);
        }

        bool exists() const
        {
            return true;
        }

        void create()
        { }

        void destroy()
        { }

        int width() const
        {
            return surface_->w;
        }

        int height() const
        {
            return surface_->h;
        }

        void *pixels()
        {
            return surface_->pixels;
        }

        void const *pixels() const
        {
            return surface_->pixels;
        }

        void flipVertical()
        {
            assert(surface_);
            int pitch = surface_->pitch;
            int size = surface_->h * pitch;
            unsigned char *pixels =
                reinterpret_cast<unsigned char *>(surface_->pixels);
            unsigned char temp[pitch];
            for (int i = 0; i < size / 2; i += pitch) {
                std::copy(pixels + i, pixels + i + pitch, temp + 0);
                std::copy(pixels + size - i - pitch, pixels + size - i,
                          pixels + i);
                std::copy(temp + 0, temp + pitch, pixels + size - i - pitch);
            }
        }

    private:
        SDL_Surface *surface_;
    };

    boost::shared_ptr<Image> createImage(int width, int height)
    {
        Uint32 redMask = 0, greenMask = 0, blueMask = 0, alphaMask = 0;
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            redMask = 0xff000000;
            greenMask = 0x00ff0000;
            blueMask = 0x0000ff00;
            alphaMask = 0x000000ff;
        } else {
            redMask = 0x000000ff;
            greenMask = 0x0000ff00;
            blueMask = 0x00ff0000;
            alphaMask = 0xff000000;
        }

        SDL_Surface *surface =
            SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
                                 redMask, greenMask, blueMask, alphaMask);
        if (surface == 0) {
            throw std::runtime_error(std::string("Failed to create image: ") +
                                     SDL_GetError());
        }
        return boost::shared_ptr<Image>(new DefaultImage(surface));
    }

    boost::shared_ptr<Image> createImage(SDL_Surface const *surface)
    {
        assert(surface);
        SDL_PixelFormat format;
        format.palette = 0;
        format.BitsPerPixel = 32;
        format.BytesPerPixel = 4;
        format.Rloss = 0;
        format.Gloss = 0;
        format.Bloss = 0;
        format.Aloss = 0;
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            format.Rshift = 24;
            format.Gshift = 16;
            format.Bshift = 8;
            format.Ashift = 0;
            format.Rmask = 0xff000000;
            format.Gmask = 0x00ff0000;
            format.Bmask = 0x0000ff00;
            format.Amask = 0x000000ff;
        } else {
            format.Rshift = 0;
            format.Gshift = 8;
            format.Bshift = 16;
            format.Ashift = 24;
            format.Rmask = 0x000000ff;
            format.Gmask = 0x0000ff00;
            format.Bmask = 0x00ff0000;
            format.Amask = 0xff000000;
        }

        SDL_Surface *convertedSurface =
            SDL_ConvertSurface(const_cast<SDL_Surface *>(surface), &format,
                               SDL_SWSURFACE);
        if (convertedSurface == 0) {
            throw std::runtime_error(std::string("Failed to convert image to RGBA format: ") +
                                     SDL_GetError());
        }
        return boost::shared_ptr<Image>(new DefaultImage(convertedSurface));
    }

    boost::shared_ptr<Image> createImage(Stream *stream, char const *type)
    {
        assert(stream);
        SDL_Surface *surface = type ?
            IMG_Load_RW(stream->rwops(), 0) :
            IMG_LoadTyped_RW(stream->rwops(), 0, const_cast<char *>(type));
        if (surface == 0) {
            throw std::runtime_error(std::string("Failed to load image: ") +
                                     SDL_GetError());
        }
        try {
            boost::shared_ptr<Image> image = createImage(surface);
            SDL_FreeSurface(surface);
            return image;
        } catch (...) {
            SDL_FreeSurface(surface);
            throw;
        }
    }
}
