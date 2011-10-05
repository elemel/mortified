#ifndef MORTIFIED_DEFAULT_FRAMEBUFFER_HPP
#define MORTIFIED_DEFAULT_FRAMEBUFFER_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Framebuffer;
    class Texture;

    boost::intrusive_ptr<Framebuffer> createFramebuffer(Texture *texture);
}

#endif
