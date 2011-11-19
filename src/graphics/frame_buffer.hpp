#ifndef MORTIFIED_FRAME_BUFFER_HPP
#define MORTIFIED_FRAME_BUFFER_HPP

#include "graphics_resource.hpp"

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Texture;

    class FrameBuffer : public virtual GraphicsResource {
    public:
        virtual int getName() const = 0;

        virtual void setColorAttachment(boost::intrusive_ptr<Texture> texture) = 0;
    };
}

#endif
