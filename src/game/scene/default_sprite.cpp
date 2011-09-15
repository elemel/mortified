#include "default_sprite.hpp"

#include "color.hpp"
#include "math.hpp"
#include "sprite.hpp"
#include "texture.hpp"

#include <stdexcept>

namespace mortified {
    class DefaultSprite :
        public virtual Sprite
    {
    public:
        explicit DefaultSprite(Texture *texture) :
            texture_(texture),
            angle_(0.0f),
            scale_(1.0f)
        { }

        Vector2 position() const
        {
            return position_;
        }

        void position(Vector2 position)
        {
            position_ = position;
        }

        float angle() const
        {
            return angle_;
        }

        void angle(float angle)
        {
            angle_ = angle;
        }

        float scale() const
        {
            return scale_;
        }

        void scale(float scale)
        {
            scale_ = scale;
        }

        Vector2 alignment() const
        {
            return alignment_;
        }

        void alignment(Vector2 alignment)
        {
            alignment_ = alignment;
        }

        Color4 color() const
        {
            return color_;
        }

        void color(Color4 color)
        {
            color_ = color;
        }

        void draw()
        {
            updateVertices();

            glColor4ub(color_.red, color_.green, color_.blue, color_.alpha);
            texture_->bind();
            glBegin(GL_QUADS);
            {
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(vertices_[0].x, vertices_[0].y);

                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(vertices_[1].x, vertices_[1].y);

                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(vertices_[2].x, vertices_[2].y);

                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(vertices_[3].x, vertices_[3].y);
            }
            glEnd();
            texture_->unbind();
        }

    private:
        Texture *texture_;
        Vector2 position_;
        float angle_;
        float scale_;
        Vector2 alignment_;
        Color4 color_;
        Vector2 vertices_[4];

        void updateVertices()
        {
            TextureSize size = texture_->size();

            Matrix3 m;
            m.translate(position_);
            m.rotate(angle_);
            m.scale(scale_);
            m.translate(Vector2(-alignment_.x * float(size.width),
                                -alignment_.y * float(size.height)));

            vertices_[0] = m * Vector2(0.0f, 0.0f);
            vertices_[1] = m * Vector2(float(size.width), 0.0f);
            vertices_[2] =
                m * Vector2(float(size.width), float(size.height));
            vertices_[3] = m * Vector2(0.0f, float(size.height));
        }
    };

    std::auto_ptr<Sprite> createSprite(Texture *texture)
    {
        return std::auto_ptr<Sprite>(new DefaultSprite(texture));
    }
}
