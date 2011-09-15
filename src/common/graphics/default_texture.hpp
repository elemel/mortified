#ifndef MORTIFIED_DEFAULT_TEXTURE_HPP
#define MORTIFIED_DEFAULT_TEXTURE_HPP

#include <memory>

namespace mortified {
    class Image;
    class Texture;

    std::auto_ptr<Texture> createTexture();
    std::auto_ptr<Texture> createTexture(Image const *image);
}

#endif
