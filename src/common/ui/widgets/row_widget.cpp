#include "row_widget.hpp"

#include "widget_base.hpp"

#include <algorithm>
#include <iostream>

namespace mortified {
    class RowWidget :
        public virtual Widget,
        private virtual WidgetBase
    {
    public:
        char const *type() const
        {
            return "row";
        }

        void measure();
        void arrange();
    };

    void RowWidget::measure()
    {
        typedef std::vector<Widget *>::iterator Iterator;

        measureChildren();

        minContentSize_ = WidgetSize();
        for (Iterator i = children_.begin(); i != children_.end(); ++i) {
            if (i != children_.begin()) {
                minContentSize_.width += style_.spacing.horizontal;
            }

            WidgetSize childMinSize = (*i)->minSize();
            minContentSize_.width += childMinSize.width;
            minContentSize_.height = std::max(minContentSize_.height,
                                              childMinSize.height);

        }
    }

    void RowWidget::arrange()
    {
        typedef std::vector<Widget *>::iterator Iterator;

        float totalWeight = 0.0f;
        for (Iterator i = children_.begin(); i != children_.end(); ++i) {
            totalWeight += (*i)->style()->weight.horizontal;
        }

        WidgetPosition origin = minContentPosition();
        WidgetSize outerSize = maxContentSize();

        int totalWidth = stretch(minContentSize_.width, outerSize.width,
                                 style_.stretch.horizontal);
        int extraWidth = totalWidth - minContentSize_.width;
        int x = (origin.x + align(totalWidth, outerSize.width,
                                  style_.alignment.horizontal));
        for (Iterator i = children_.begin(); i != children_.end(); ++i) {
            float fraction = (totalWeight ?
                              (*i)->style()->weight.horizontal / totalWeight :
                              1.0f / float(children_.size()));

            WidgetSize innerSize = (*i)->minSize();
            int width = (innerSize.width +
                         int(fraction * float(extraWidth) + 0.5f));
            int height = stretch(innerSize.height, outerSize.height,
                                 style_.stretch.vertical);
            int y = (origin.y + align(height, outerSize.height,
                                      style_.alignment.vertical));

            (*i)->position(WidgetPosition(x, y));
            (*i)->size(WidgetSize(width, height));

            x += width + style_.spacing.horizontal;
        }

        arrangeChildren();
    }

    std::auto_ptr<Widget> createRowWidget()
    {
        return std::auto_ptr<Widget>(new RowWidget);
    }
}
