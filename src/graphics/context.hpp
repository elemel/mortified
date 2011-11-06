#ifndef MORTIFIED_CONTEXT_HPP
#define MORTIFIED_CONTEXT_HPP

#include "graphics_resource.hpp"

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Texture;
    class TextureSource;

    class Context : public virtual GraphicsResource {
    public:
        virtual bool multisample() const = 0;
        virtual void multisample(bool multisample) = 0;

        virtual boost::intrusive_ptr<Texture>
        createTexture(boost::intrusive_ptr<TextureSource> source) = 0;

        virtual boost::intrusive_ptr<Texture>
        createTexture(int width, int height) = 0;
    };
}

#endif
