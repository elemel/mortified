#include "default_sprite.hpp"

#include "color.hpp"
#include "context.hpp"
#include "default_texture.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "math.hpp"
#include "render_service.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "texture.hpp"

namespace mortified {
    class DefaultSprite : public virtual Sprite {
    public:
        DefaultSprite(Scene *scene, int layerIndex) :
            scene_(scene),
            layerIndex_(layerIndex),
            angle_(0.0f),
            scale_(1.0f),
            dirtyVertices_(true)
        { }

        int getLayerIndex() const
        {
            return layerIndex_;
        }
        
        boost::intrusive_ptr<Image> getImage()
        {
            return image_;
        }

        void setImage(boost::intrusive_ptr<Image> image)
        {
            image_ = image;
            dirtyVertices_ = true;
        }

        Vector2 getPosition() const
        {
            return position_;
        }

        void setPosition(Vector2 position)
        {
            position_ = position;
            dirtyVertices_ = true;
        }

        float getAngle() const
        {
            return angle_;
        }

        void setAngle(float angle)
        {
            angle_ = angle;
            dirtyVertices_ = true;
        }

        Vector2 getScale() const
        {
            return scale_;
        }

        void setScale(Vector2 scale)
        {
            scale_ = scale;
            dirtyVertices_ = true;
        }

        Vector2 getAlignment() const
        {
            return alignment_;
        }

        void setAlignment(Vector2 alignment)
        {
            alignment_ = alignment;
            dirtyVertices_ = true;
        }

        Color4 getColor() const
        {
            return color_;
        }

        void setColor(Color4 color)
        {
            color_ = color;
        }

        void draw()
        {
            updateTexture();
            updateVertices();

            if (texture_) {
                texture_->create();

                glColor4ub(color_.red, color_.green, color_.blue, color_.alpha);
                glMultiTexCoord1f(GL_TEXTURE1, 2.0f);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texture_->getName());
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
        }

    private:
        Scene *scene_;
        int layerIndex_;
        boost::intrusive_ptr<Image> image_;
        boost::intrusive_ptr<Texture> texture_;
        Vector2 position_;
        float angle_;
        Vector2 scale_;
        Vector2 alignment_;
        Color4 color_;
        Vector2 vertices_[4];
        bool dirtyVertices_;

        void updateTexture()
        {
            if (image_ && !texture_) {
                texture_ = createTexture(scene_->getContext());
                texture_->setSource(createImageTextureSource(image_));
            }
        }

        void updateVertices()
        {
            if (texture_ && dirtyVertices_) {
                texture_->create();
                Vector2 size(float(texture_->getWidth()),
                             float(texture_->getHeight()));
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

    std::auto_ptr<Sprite> createSprite(Scene *scene, int layerIndex)
    {
        return std::auto_ptr<Sprite>(new DefaultSprite(scene, layerIndex));
    }
}
