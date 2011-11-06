#ifndef MORTIFIED_TEXT_WIDGET_HPP
#define MORTIFIED_TEXT_WIDGET_HPP

#include "widget.hpp"

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Font;

    class TextWidget : public virtual Widget {
    public:
        virtual boost::intrusive_ptr<Font> font() const = 0;
        virtual void font(boost::intrusive_ptr<Font> font) = 0;

        virtual char const *text() const = 0;
        virtual void text(char const *text) = 0;
    };
}

#endif
