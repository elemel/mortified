#ifndef MORTIFIED_EMPTY_TEXTURE_SOURCE_HPP
#define MORTIFIED_EMPTY_TEXTURE_SOURCE_HPP

#include <boost/shared_ptr.hpp>

namespace mortified {
    class TextureSource;

    boost::shared_ptr<TextureSource>
        createEmptyTextureSource(int width, int height);
}

#endif