#ifndef MORTIFIED_CONTEXT_HPP
#define MORTIFIED_CONTEXT_HPP

#include "graphics_resource.hpp"

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class FrameBuffer;
    class Texture;
    class TextureSource;

    class Context : public virtual GraphicsResource {
    public:
        virtual boost::intrusive_ptr<Texture> createTexture() = 0;

        virtual boost::intrusive_ptr<FrameBuffer> createFrameBuffer() = 0;
    };
}

#endif
