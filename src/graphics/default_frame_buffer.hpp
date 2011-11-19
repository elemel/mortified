#ifndef MORTIFIED_DEFAULT_FRAME_BUFFER_HPP
#define MORTIFIED_DEFAULT_FRAME_BUFFER_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class FrameBuffer;
    class Context;

    boost::intrusive_ptr<FrameBuffer>
    createFrameBuffer(boost::intrusive_ptr<Context> context);
}

#endif
