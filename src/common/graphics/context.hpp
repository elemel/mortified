#ifndef MORTIFIED_CONTEXT_HPP
#define MORTIFIED_CONTEXT_HPP

#include "graphics_object.hpp"

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class Texture;
    class TextureSource;

    class Context : public virtual GraphicsObject {
    public:
        virtual ~Context()
        { }

        virtual boost::intrusive_ptr<Texture>
            createTexture(boost::shared_ptr<TextureSource> source) = 0;

        virtual boost::intrusive_ptr<Texture>
            createEmptyTexture(int width, int height) = 0;
    };
}

#endif
