#ifndef MORTIFIED_IMAGE_SPRITE_HPP
#define MORTIFIED_IMAGE_SPRITE_HPP

#include "color.hpp"
#include "math.hpp"
#include "sprite.hpp"

namespace mortified {
    class Color4;
    class Vector2;

    class ImageSprite : public virtual Sprite {
    public:
        virtual Vector2 getPosition() const = 0;
        virtual void setPosition(Vector2 position) = 0;

        virtual float getAngle() const = 0;
        virtual void setAngle(float angle) = 0;
        
        virtual Vector2 getScale() const = 0;
        virtual void setScale(Vector2 scale) = 0;

        virtual Vector2 getAlignment() const = 0;
        virtual void setAlignment(Vector2 alignment) = 0;

        virtual Color4 getColor() const = 0;
        virtual void setColor(Color4 color) = 0;
    };
}

#endif
