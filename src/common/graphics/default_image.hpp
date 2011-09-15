#ifndef MORTIFIED_DEFAULT_IMAGE_HPP
#define MORTIFIED_DEFAULT_IMAGE_HPP

#include <memory>
#include <SDL/SDL_surface.h>

namespace mortified {
    class Image;
    class ImageSize;
    class Stream;

    std::auto_ptr<Image> createImage(ImageSize size);
    std::auto_ptr<Image> createImage(SDL_Surface const *surface);
    std::auto_ptr<Image> createImage(Stream *stream, char const *type = 0);
}

#endif
