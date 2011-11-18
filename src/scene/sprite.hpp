#ifndef MORTIFIED_SPRITE_HPP
#define MORTIFIED_SPRITE_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Color4;
    class Image;
    class Vector2;

    class Sprite {
    public:
        virtual ~Sprite()
        { }

        virtual int getLayerIndex() const = 0;
        
        virtual boost::intrusive_ptr<Image> getImage() = 0;
        virtual void setImage(boost::intrusive_ptr<Image> image) = 0;

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

        virtual void draw() = 0;
    };
}

#endif
