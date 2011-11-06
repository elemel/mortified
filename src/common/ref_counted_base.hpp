#ifndef MORTIFIED_REF_COUNTED_BASE_HPP
#define MORTIFIED_REF_COUNTED_BASE_HPP

#include "ref_counted.hpp"

namespace mortified {
    class RefCountedBase : public virtual RefCounted {
    public:
        RefCountedBase() :
            refCount_(0)
        { }

        void addRef() const
        {
            ++refCount_;
        }
        
        void release() const
        {
            if (--refCount_ <= 0) {
                delete this;
            }
        }

    protected:
        mutable int refCount_;
    };
}

#endif
