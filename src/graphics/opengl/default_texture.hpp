#ifndef MORTIFIED_DEFAULT_TEXTURE_HPP
#define MORTIFIED_DEFAULT_TEXTURE_HPP

#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class Context;
    class Texture;

    boost::intrusive_ptr<Texture>
    createTexture(boost::intrusive_ptr<Context> context);
}

#endif
