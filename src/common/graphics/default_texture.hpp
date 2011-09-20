#ifndef MORTIFIED_DEFAULT_TEXTURE_HPP
#define MORTIFIED_DEFAULT_TEXTURE_HPP

#include <boost/shared_ptr.hpp>

#include <SDL/SDL_opengl.h>

namespace mortified {
    class Texture;
    class TextureSource;

    boost::shared_ptr<Texture> createTexture(boost::shared_ptr<TextureSource const> source);
}

#endif
