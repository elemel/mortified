#include "default_image.hpp"

#include "image.hpp"
#include "ref_counted_base.hpp"
#include "stream.hpp"

#include <SDL/SDL_image.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace mortified {
    class DefaultImage :
        public virtual Image,
        private virtual RefCountedBase
    {
    public:
        explicit DefaultImage(SDL_Surface *surface) :
            surface_(surface)
        { }

        ~DefaultImage()
        {
            SDL_FreeSurface(surface_);
        }

        void convert()
        {
            SDL_Surface *convertedSurface =
                SDL_ConvertSurfaceFormat(const_cast<SDL_Surface *>(surface_),
                                         SDL_PIXELFORMAT_ABGR8888, 0);
            if (convertedSurface == 0) {
                throw std::runtime_error(std::string("Failed to convert image to RGBA format: ") +
                                         SDL_GetError());
            }
            SDL_FreeSurface(surface_);
            surface_ = convertedSurface;
        }

        int getWidth() const
        {
            return surface_->w;
        }

        int getHeight() const
        {
            return surface_->h;
        }

        void *getPixels()
        {
            return surface_->pixels;
        }

        void const *getPixels() const
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

    boost::intrusive_ptr<Image> createImage(int width, int height)
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
        return boost::intrusive_ptr<Image>(new DefaultImage(surface));
    }

    boost::intrusive_ptr<Image> adoptImage(SDL_Surface *surface)
    {
        boost::intrusive_ptr<Image> result(new DefaultImage(surface));
        result->convert();
        return result;
    }

    boost::intrusive_ptr<Image> loadImage(Stream *stream)
    {
        SDL_Surface *surface = IMG_Load_RW(stream->rwops(), 0);
        if (surface == 0) {
            throw std::runtime_error(std::string("Failed to load image: ") +
                                     SDL_GetError());
        }
        return adoptImage(surface);
    }

    boost::intrusive_ptr<Image> loadImageFromFile(char const *file)
    {
        SDL_Surface *surface = IMG_Load(file);
        if (surface == 0) {
            std::stringstream message;
            message << "Failed to load image from file \"" << file << "\":"
                    << SDL_GetError();            
            throw std::runtime_error(message.str());
        }
        return adoptImage(surface);
    }
}
