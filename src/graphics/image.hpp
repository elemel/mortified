#ifndef MORTIFIED_IMAGE_HPP
#define MORTIFIED_IMAGE_HPP

#include "ref_counted.hpp"

namespace mortified {
    class Image : public virtual RefCounted {
    public:
        virtual ~Image()
        { }

        virtual void convert() = 0;

        virtual int width() const = 0;
        virtual int height() const = 0;

        virtual void *pixels() = 0;
        virtual void const *pixels() const = 0;

        virtual void flipVertical() = 0;
    };
}

#endif
