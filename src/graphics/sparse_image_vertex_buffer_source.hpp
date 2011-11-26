#ifndef MORTIFIED_SPARSE_IMAGE_VERTEX_BUFFER_SOURCE_HPP
#define MORTIFIED_SPARSE_IMAGE_VERTEX_BUFFER_SOURCE_HPP

#include <memory>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class SparseImage;
    class VertexBufferSource;

    std::auto_ptr<VertexBufferSource>
    createSparseImageVertexBufferSource(boost::intrusive_ptr<SparseImage> image);
}

#endif
