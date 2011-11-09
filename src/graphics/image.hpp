#ifndef MORTIFIED_IMAGE_HPP
#define MORTIFIED_IMAGE_HPP

#include "ref_counted.hpp"

namespace mortified {
    class Image : public virtual RefCounted {
    public:
        virtual ~Image()
        { }

        virtual void convert() = 0;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual void *getPixels() = 0;
        virtual void const *getPixels() const = 0;

        virtual void flipVertical() = 0;
    };
}

#endif
