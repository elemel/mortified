#ifndef MORTIFIED_DEFAULT_IMAGE_HPP
#define MORTIFIED_DEFAULT_IMAGE_HPP

#include <boost/shared_ptr.hpp>
#include <SDL/SDL_surface.h>

namespace mortified {
    class Image;
    class Stream;

    boost::shared_ptr<Image> createImage(int width, int height);
    boost::shared_ptr<Image> createImage(SDL_Surface const *surface);
    boost::shared_ptr<Image> createImage(Stream *stream, char const *type = 0);
}

#endif
