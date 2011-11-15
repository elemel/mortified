#ifndef MORTIFIED_DEFAULT_SPARSE_IMAGE_HPP
#define MORTIFIED_DEFAULT_SPARSE_IMAGE_HPP

#include <memory>

namespace mortified {
    class SparseImage;
    
    std::auto_ptr<SparseImage> createSparseImage();
}

#endif
