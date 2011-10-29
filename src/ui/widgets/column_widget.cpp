#include "column_widget.hpp"

#include "widget_base.hpp"

#include <algorithm>
#include <iostream>

namespace mortified {
    class ColumnWidget :
        public virtual Widget,
        private virtual WidgetBase
    {
    public:
        char const *type() const
        {
            return "column";
        }

        void measure();
        void arrange();
    };

    void ColumnWidget::measure()
    {
        typedef std::vector<Widget *>::iterator Iterator;

        measureChildren();

        minContentSize_ = WidgetSize();
        for (Iterator i = children_.begin(); i != children_.end(); ++i) {
            if (i != children_.begin()) {
                minContentSize_.height += style_.spacing.vertical;
            }

            WidgetSize childMinSize = (*i)->minSize();
            minContentSize_.width = std::max(minContentSize_.width,
                                             childMinSize.width);
            minContentSize_.height += childMinSize.height;
        }
    }

    void ColumnWidget::arrange()
    {
        typedef std::vector<Widget *>::iterator Iterator;

        float totalWeight = 0.0f;
        for (Iterator i = children_.begin(); i != children_.end(); ++i) {
            totalWeight += (*i)->style()->weight.vertical;
        }

        WidgetPosition origin = minContentPosition();
        WidgetSize outerSize = maxContentSize();

        int totalHeight = stretch(minContentSize_.height, outerSize.height,
                                  style_.stretch.vertical);

        int extraHeight = totalHeight - minContentSize_.height;
        int y = (origin.y + align(totalHeight, outerSize.height,
                                  style_.alignment.vertical));
        for (Iterator i = children_.begin(); i != children_.end(); ++i) {
            float fraction = (totalWeight ?
                              (*i)->style()->weight.vertical / totalWeight :
                              1.0f / float(children_.size()));

            WidgetSize innerSize = (*i)->minSize();
            int width = stretch(innerSize.width, outerSize.width,
                                style_.stretch.horizontal);
            int height = (innerSize.height +
                         int(fraction * float(extraHeight) + 0.5f));
            int x = (origin.x + align(width, outerSize.width,
                                      style_.alignment.horizontal));

            (*i)->position(WidgetPosition(x, y));
            (*i)->size(WidgetSize(width, height));

            y += height + style_.spacing.vertical;
        }

        arrangeChildren();
    }

    std::auto_ptr<Widget> createColumnWidget()
    {
        return std::auto_ptr<Widget>(new ColumnWidget);
    }
}
