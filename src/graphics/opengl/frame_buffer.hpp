#ifndef MORTIFIED_FRAME_BUFFER_HPP
#define MORTIFIED_FRAME_BUFFER_HPP

#include "graphics_resource.hpp"

#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class Texture;

    class FrameBuffer : public virtual GraphicsResource {
    public:
        virtual GLuint getName() const = 0;

        virtual void setColorAttachment(boost::intrusive_ptr<Texture> texture) = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}

#endif
