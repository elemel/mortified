#include "default_sprite.hpp"

#include "color.hpp"
#include "math.hpp"
#include "scene_object_base.hpp"
#include "sprite.hpp"
#include "texture.hpp"

namespace mortified {
    class DefaultSprite :
        public virtual Sprite,
        private virtual SceneObjectBase
    {
    public:
        explicit DefaultSprite(boost::shared_ptr<Texture> texture) :
            texture_(texture),
            angle_(0.0f),
            scale_(1.0f),
            dirtyVertices_(true)
        { }

        Vector2 position() const
        {
            return position_;
        }

        void position(Vector2 position)
        {
            position_ = position;
            dirtyVertices_ = true;
        }

        float angle() const
        {
            return angle_;
        }

        void angle(float angle)
        {
            angle_ = angle;
            dirtyVertices_ = true;
        }

        Vector2 scale() const
        {
            return scale_;
        }

        void scale(Vector2 scale)
        {
            scale_ = scale;
            dirtyVertices_ = true;
        }

        Vector2 alignment() const
        {
            return alignment_;
        }

        void alignment(Vector2 alignment)
        {
            alignment_ = alignment;
            dirtyVertices_ = true;
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
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_->name());
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
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }

    private:
        boost::shared_ptr<Texture> texture_;
        Vector2 position_;
        float angle_;
        Vector2 scale_;
        Vector2 alignment_;
        Color4 color_;
        Vector2 vertices_[4];
        bool dirtyVertices_;

        void updateVertices()
        {
            if (dirtyVertices_) {
                texture_->create();
                Vector2 size(float(texture_->width()),
                             float(texture_->height()));
                Matrix3 m;
                m.translate(position_);
                m.rotate(angle_);
                m.scale(scale_);
                m.translate(Vector2(-alignment_.x * size.x,
                                    -alignment_.y * size.y));
                
                vertices_[0] = m * Vector2(0.0f, 0.0f);
                vertices_[1] = m * Vector2(size.x, 0.0f);
                vertices_[2] = m * Vector2(size.x, size.y);
                vertices_[3] = m * Vector2(0.0f, size.y);

                dirtyVertices_ = false;
            }
        }
    };

    boost::shared_ptr<Sprite> createSprite(boost::shared_ptr<Texture> texture)
    {
        return boost::shared_ptr<Sprite>(new DefaultSprite(texture));
    }
}