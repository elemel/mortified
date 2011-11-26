#ifndef MORTIFIED_DEFAULT_SPARSE_IMAGE_HPP
#define MORTIFIED_DEFAULT_SPARSE_IMAGE_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class SparseImage;
    
    boost::intrusive_ptr<SparseImage> createSparseImage();
}

#endif
