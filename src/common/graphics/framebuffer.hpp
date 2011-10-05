#ifndef MORTIFIED_FRAMEBUFFER_HPP
#define MORTIFIED_FRAMEBUFFER_HPP

#include "graphics_resource.hpp"

namespace mortified {
    class Framebuffer : public virtual GraphicsResource {
    public:
        virtual int name() const = 0;
    };
}

#endif