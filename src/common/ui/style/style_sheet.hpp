#ifndef MORTIFIED_STYLE_SHEET_HPP
#define MORTIFIED_STYLE_SHEET_HPP

#include <map>
#include <memory>
#include <string>

namespace mortified {
    class WidgetStyle;

    class StyleMask {
    public:
        bool weight : 1;
        bool stretch : 1;
        bool alignment : 1;

        bool padding : 1;
        bool border : 1;
        bool spacing : 1;

        bool color : 1;
        bool backgroundColor : 1;
        bool borderColor : 1;

        StyleMask() :
            weight(false),
            stretch(false),
            alignment(false),

            padding(false),
            border(false),
            spacing(false),

            color(false),
            backgroundColor(false),
            borderColor(false)
        { }
    };

    class StyleSheet {
    public:
        virtual ~StyleSheet()
        { }

        virtual void
            updateStyles(std::string const *names, int nameCount,
                         std::string const *bases, int baseCount,
                         WidgetStyle const *style, StyleMask mask) = 0;

        virtual std::auto_ptr<WidgetStyle>
            applyStyles(std::string const *names, int nameCount) = 0;
    };
}

#endif
