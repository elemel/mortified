#ifndef MORTIFIED_CONTEXT_HPP
#define MORTIFIED_CONTEXT_HPP

#include "graphics_resource.hpp"

#include <boost/shared_ptr.hpp>

namespace mortified {
    class Texture;
    class TextureSource;

    class Context : public virtual GraphicsResource {
    public:
        virtual boost::shared_ptr<Texture>
        createTexture(boost::shared_ptr<TextureSource> source) = 0;

        virtual boost::shared_ptr<Texture>
        createTexture(int width, int height) = 0;
    };
}

#endif
