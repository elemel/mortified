#ifndef MORTIFIED_SPARSE_IMAGE_HPP
#define MORTIFIED_SPARSE_IMAGE_HPP

#include <utility>

namespace mortified {
    class Color4;

    class SparseImage {
    public:
        struct Pixel {
            short x;
            short y;
            unsigned char red;
            unsigned char green;
            unsigned char blue;
            unsigned char alpha;
        };

        virtual ~SparseImage()
        { }

        virtual int getX() const = 0;
        virtual int getY() const = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual Color4 getPixel(int x, int y) const = 0;
        virtual void setPixel(int x, int y, Color4 color) = 0;

        virtual int getSize() const = 0;
        virtual Pixel const *getData() const = 0;
        
        virtual void normalize() = 0;
        virtual void draw() = 0;
    };
}

#endif
