#ifndef MORTIFIED_DEFAULT_IMAGE_SPRITE_HPP
#define MORTIFIED_DEFAULT_IMAGE_SPRITE_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class ImageSprite;
    class Texture;

    boost::intrusive_ptr<ImageSprite>
    createImageSprite(boost::intrusive_ptr<Texture> texture);
}

#endif
