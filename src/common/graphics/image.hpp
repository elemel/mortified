#ifndef MORTIFIED_IMAGE_HPP
#define MORTIFIED_IMAGE_HPP

namespace mortified {
    class ImageSize {
    public:
        int width;
        int height;

        explicit ImageSize(int size = 0) :
            width(size),
            height(size)
        { }

        ImageSize(int width, int height) :
            width(width),
            height(height)
        { }
    };

    // Image in RGBA format.
    class Image {
    public:
        virtual ~Image()
        { }

        virtual ImageSize size() const = 0;

        virtual unsigned char *data() = 0;
        virtual unsigned char const *data() const = 0;

        virtual void flipVertical() = 0;
    };
}

#endif
