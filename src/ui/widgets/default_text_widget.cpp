#include "default_text_widget.hpp"

#include "context.hpp"
#include "default_font.hpp"
#include "default_image.hpp"
#include "default_texture.hpp"
#include "font.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
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
        explicit DefaultTextWidget(boost::intrusive_ptr<Context> context) :
            context_(context)
        { }

        char const *type() const
        {
            return "text";
        }

        boost::intrusive_ptr<Font> font() const
        {
            return font_;
        }

        void font(boost::intrusive_ptr<Font> font)
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
                texture_ = context_->createTexture();
                texture_->setSource(createImageTextureSource(image_));
            }
    
            if (image_) {
                minContentSize_ = WidgetSize(image_->getWidth(), image_->getHeight());
            } else {
                minContentSize_ = WidgetSize();
            }
        }
    
        void draw()
        {
            drawBackground();
    
            if (texture_) {
                texture_->create();

                WidgetPosition origin = minContentPosition();
                WidgetSize outerSize = maxContentSize();
        
                int width = texture_->getWidth();
                int height = texture_->getHeight();
        
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
                glBindTexture(GL_TEXTURE_2D, texture_->getName());
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
                glBindTexture(GL_TEXTURE_2D, 0);
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
        boost::intrusive_ptr<Context> context_;
        boost::intrusive_ptr<Font> font_;
        std::string text_;

        boost::intrusive_ptr<Image> image_;
        boost::intrusive_ptr<Texture> texture_;
    };

    std::auto_ptr<Widget>
    createTextWidget(boost::intrusive_ptr<Context> context)
    {
        return std::auto_ptr<Widget>(new DefaultTextWidget(context));
    }
}
