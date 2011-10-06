#ifndef MORTIFIED_FRAMEBUFFER_HPP
#define MORTIFIED_FRAMEBUFFER_HPP

#include "graphics_object.hpp"

namespace mortified {
    class Framebuffer : public virtual GraphicsObject {
    public:
        virtual int name() const = 0;
    };
}

#endif
