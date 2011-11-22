#ifndef MORTIFIED_IMAGE_TEXTURE_SOURCE_HPP
#define MORTIFIED_IMAGE_TEXTURE_SOURCE_HPP

#include "texture_source.hpp"

#include <memory>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Image;

    std::auto_ptr<TextureSource>
    createImageTextureSource(boost::intrusive_ptr<Image> image);
}

#endif
