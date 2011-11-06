#ifndef MORTIFIED_IMAGE_TEXTURE_SOURCE_HPP
#define MORTIFIED_IMAGE_TEXTURE_SOURCE_HPP

#include "texture_source.hpp"

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Image;

    boost::intrusive_ptr<TextureSource>
    createImageTextureSource(boost::intrusive_ptr<Image> image);
}

#endif
