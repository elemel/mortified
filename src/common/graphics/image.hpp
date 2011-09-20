#ifndef MORTIFIED_IMAGE_HPP
#define MORTIFIED_IMAGE_HPP

#include "texture_source.hpp"

namespace mortified {
    class Image : public virtual TextureSource {
    public:
        virtual ~Image()
        { }

        virtual void *pixels() = 0;

        virtual void flipVertical() = 0;
    };
}

#endif
