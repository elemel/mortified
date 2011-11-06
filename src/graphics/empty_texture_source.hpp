#ifndef MORTIFIED_EMPTY_TEXTURE_SOURCE_HPP
#define MORTIFIED_EMPTY_TEXTURE_SOURCE_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class TextureSource;

    boost::intrusive_ptr<TextureSource>
    createEmptyTextureSource(int width, int height);
}

#endif