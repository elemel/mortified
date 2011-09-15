#include "default_text_widget.hpp"

#include "default_font.hpp"
#include "default_image.hpp"
#include "default_texture.hpp"
#include "font.hpp"
#include "image.hpp"
#include "text_widget.hpp"
#include "texture.hpp"
#include "widget_base.hpp"

#include <iostream>
#include <string>

namespace mortified {
    class DefaultTextWidget :
        public virtual TextWidget,
        private virtual WidgetBase
    {
    public:
        char const *type() const
        {
            return "text";
        }

        boost::shared_ptr<Font> font() const
        {
            return font_;
        }

        void font(boost::shared_ptr<Font> font)
        {
            font_ = font;
        }

        char const *text() const
        {
            return text_.c_str();
        }

        void text(char const *text)
        {
            text_ = text;
        }

        void measure()
        {
            if (image_.get() == 0 && font_ && !text_.empty()) {
                image_ = font_->render(text_.c_str());
                texture_ = createTexture(image_.get());
            }
    
            if (image_.get()) {
                ImageSize imageSize = image_->size();
                minContentSize_ = WidgetSize(imageSize.width, imageSize.height);
            } else {
                minContentSize_ = WidgetSize();
            }
        }
    
        void draw()
        {
            drawBackground();
    
            if (texture_.get()) {
                WidgetPosition origin = minContentPosition();
                WidgetSize outerSize = maxContentSize();
        
                TextureSize textureSize = texture_->size();
                int width = textureSize.width;
                int height = textureSize.height;
        
                int x = (position_.x + origin.x +
                         align(width, outerSize.width,
                               style_.alignment.horizontal));
                int y = (position_.y + origin.y +
                         align(height, outerSize.height,
                               style_.alignment.vertical));
        
                glColor4ub(style_.color.red,
                           style_.color.green,
                           style_.color.blue,
                           style_.color.alpha);
                texture_->bind();
                glBegin(GL_QUADS);
                {
                    glTexCoord2i(0, 0);
                    glVertex2i(x, y);
                    glTexCoord2i(1, 0);
                    glVertex2f(x + width, y);
                    glTexCoord2i(1, 1);
                    glVertex2f(x + width, y + height);
                    glTexCoord2i(0, 1);
                    glVertex2i(x, y + height);
                }
                glEnd();
                texture_->unbind();
            }
    
            drawBorder();
        }

        TextWidget *asTextWidget()
        {
            return this;
        }

        TextWidget const *asTextWidget() const
        {
            return this;
        }

    private:
        boost::shared_ptr<Font> font_;
        std::string text_;

        std::auto_ptr<Image> image_;
        std::auto_ptr<Texture> texture_;
    };

    std::auto_ptr<Widget> createTextWidget()
    {
        return std::auto_ptr<Widget>(new DefaultTextWidget);
    }
}