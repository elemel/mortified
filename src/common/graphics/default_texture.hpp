#ifndef MORTIFIED_DEFAULT_TEXTURE_HPP
#define MORTIFIED_DEFAULT_TEXTURE_HPP

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <SDL/SDL_opengl.h>

namespace mortified {
    class Context;
    class Texture;
    class TextureSource;

    boost::intrusive_ptr<Texture>
        createTexture(Context *context, boost::shared_ptr<TextureSource> source);
}

#endif
