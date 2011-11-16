#ifndef MORTIFIED_DEFAULT_IMAGE_SPRITE_HPP
#define MORTIFIED_DEFAULT_IMAGE_SPRITE_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class ImageSprite;
    class RenderService;

    boost::intrusive_ptr<ImageSprite>
    createImageSprite(RenderService *service);
}

#endif
