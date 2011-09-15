#ifndef MORTIFIED_CAMERA_HPP
#define MORTIFIED_CAMERA_HPP

namespace mortified {
    class Vector2;

    class Camera {
    public:
        virtual ~Camera()
        { }

        virtual Vector2 position() const = 0;
        virtual void position(Vector2 position) = 0;

        virtual float scale() const = 0;
        virtual void scale(float scale) = 0;

        virtual float aspectRatio() const = 0;
        virtual void aspectRatio(float aspectRatio) = 0;

        virtual void apply() = 0;
    };
}

#endif
