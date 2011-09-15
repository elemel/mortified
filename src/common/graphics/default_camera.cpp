#include "default_camera.hpp"

#include "camera.hpp"
#include "math.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultCamera :
        public virtual Camera
    {
    public:
        DefaultCamera() :
            scale_(1.0f),
            aspectRatio_(1.0f)
        { }

        Vector2 position() const
        {
            return position_;
        }

        void position(Vector2 position)
        {
            position_ = position;
        }

        float scale() const
        {
            return scale_;
        }

        void scale(float scale)
        {
            scale_ = scale;
        }

        float aspectRatio() const
        {
            return aspectRatio_;
        }

        void aspectRatio(float aspectRatio)
        {
            aspectRatio_ = aspectRatio;
        }

        void apply()
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(position_.x - scale_ * aspectRatio_,
                    position_.x + scale_ * aspectRatio_,
                    position_.y - scale_, position_.y + scale_, -1.0f, 1.0f);
            glMatrixMode(GL_MODELVIEW);
        }

    private:
        Vector2 position_;
        float scale_;
        float aspectRatio_;
    };

    std::auto_ptr<Camera> createCamera()
    {
        return std::auto_ptr<Camera>(new DefaultCamera);
    }
}
