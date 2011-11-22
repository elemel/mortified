#ifndef MORTIFIED_DEFAULT_VERTEX_BUFFER_HPP
#define MORTIFIED_DEFAULT_VERTEX_BUFFER_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class VertexBuffer;

    boost::intrusive_ptr<VertexBuffer>
    createVertexBuffer(boost::intrusive_ptr<Context> context);
}

#endif
