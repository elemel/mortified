#ifndef MORTIFIED_DEFAULT_IMAGE_HPP
#define MORTIFIED_DEFAULT_IMAGE_HPP

#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL_surface.h>

namespace mortified {
    class Image;
    class Stream;

    boost::intrusive_ptr<Image> createImage(int width, int height);
    boost::intrusive_ptr<Image> adoptImage(SDL_Surface *surface);
    boost::intrusive_ptr<Image> loadImage(Stream *stream);
    boost::intrusive_ptr<Image> loadImageFromFile(char const *file);
}

#endif
