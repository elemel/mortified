#ifndef MORTIFIED_REF_COUNTED_HPP
#define MORTIFIED_REF_COUNTED_HPP

namespace mortified {
    class RefCounted {
    public:
        virtual ~RefCounted()
        { }

        virtual void addRef() const = 0;
        virtual void release() const = 0;
    };

    inline void intrusive_ptr_add_ref(RefCounted const *refCounted)
    {
        refCounted->addRef();
    }
    
    inline void intrusive_ptr_release(RefCounted const *refCounted)
    {
        refCounted->release();
    }
}

#endif
