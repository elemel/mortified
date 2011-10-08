#ifndef MORTIFIED_DEFAULT_FRAMEBUFFER_HPP
#define MORTIFIED_DEFAULT_FRAMEBUFFER_HPP

#include <boost/shared_ptr.hpp>

namespace mortified {
    class Framebuffer;
    class Texture;

    boost::shared_ptr<Framebuffer> createFramebuffer(boost::shared_ptr<Texture> texture);
}

#endif
