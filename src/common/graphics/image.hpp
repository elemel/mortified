#ifndef MORTIFIED_IMAGE_HPP
#define MORTIFIED_IMAGE_HPP

namespace mortified {
    class Image {
    public:
        virtual ~Image()
        { }

        virtual int width() const = 0;
        virtual int height() const = 0;

        virtual void *pixels() = 0;
        virtual void const *pixels() const = 0;

        virtual void flipVertical() = 0;
    };
}

#endif
