#ifndef MORTIFIED_SPRITE_HPP
#define MORTIFIED_SPRITE_HPP

namespace mortified {
    class Color4;
    class Vector2;

    class Sprite {
    public:
        virtual ~Sprite()
        { }

        virtual Vector2 position() const = 0;
        virtual void position(Vector2 position) = 0;

        virtual float scale() const = 0;
        virtual void scale(float scale) = 0;

        virtual float angle() const = 0;
        virtual void angle(float angle) = 0;

        virtual Vector2 alignment() const = 0;
        virtual void alignment(Vector2 alignment) = 0;

        virtual Color4 color() const = 0;
        virtual void color(Color4 color) = 0;

        virtual void draw() = 0;
    };
}

#endif
