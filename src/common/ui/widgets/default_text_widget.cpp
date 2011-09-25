#include "default_text_widget.hpp"

#include "default_font.hpp"
#include "default_image.hpp"
#include "default_texture.hpp"
#include "font.hpp"
#include "graphics_manager.hpp"
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
        explicit DefaultTextWidget(boost::shared_ptr<GraphicsManager> graphicsManager) :
            graphicsManager_(graphicsManager)
        { }

        ~DefaultTextWidget()
        {
            if (texture_) {
                graphicsManager_->removeResource(textureIterator_);
            }
        }

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
                if (texture_) {
                    graphicsManager_->removeResource(textureIterator_);
                }
                texture_ = createTexture(image_);
                textureIterator_ = graphicsManager_->addResource(texture_);
            }
    
            if (image_) {
                minContentSize_ = WidgetSize(image_->width(), image_->height());
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
        
                int width = texture_->width();
                int height = texture_->height();
        
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
                glBindTexture(GL_TEXTURE_2D, texture_->name());
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
        boost::shared_ptr<GraphicsManager> graphicsManager_;
        boost::shared_ptr<Font> font_;
        std::string text_;

        boost::shared_ptr<Image> image_;
        boost::shared_ptr<Texture> texture_;
        GraphicsManager::ResourceIterator textureIterator_;
    };

    std::auto_ptr<Widget>
        createTextWidget(boost::shared_ptr<GraphicsManager> graphicsManager)
    {
        return std::auto_ptr<Widget>(new DefaultTextWidget(graphicsManager));
    }
}
