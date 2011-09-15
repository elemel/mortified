#ifndef MORTIFIED_DEFAULT_FRAMEBUFFER_HPP
#define MORTIFIED_DEFAULT_FRAMEBUFFER_HPP

#include <memory>

namespace mortified {
    class Framebuffer;

    std::auto_ptr<Framebuffer> createFramebuffer(int width, int height);
}

#endif
