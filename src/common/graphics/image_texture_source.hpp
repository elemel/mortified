#ifndef MORTIFIED_IMAGE_TEXTURE_SOURCE_HPP
#define MORTIFIED_IMAGE_TEXTURE_SOURCE_HPP

#include "texture_source.hpp"

#include <boost/shared_ptr.hpp>

namespace mortified {
    class Image;

    boost::shared_ptr<TextureSource>
        createImageTextureSource(boost::shared_ptr<Image> image);
}

#endif
