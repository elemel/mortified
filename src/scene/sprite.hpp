#ifndef MORTIFIED_SPRITE_HPP
#define MORTIFIED_SPRITE_HPP

#include "ref_counted.hpp"

namespace mortified {
    class Sprite : public virtual RefCounted {
    public:
        virtual ~Sprite()
        { }
        
        virtual void draw() = 0;
    };
}

#endif
