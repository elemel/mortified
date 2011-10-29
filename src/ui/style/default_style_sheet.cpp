#include "default_style_sheet.hpp"

#include "style_sheet.hpp"
#include "widget.hpp"

#include <iostream>
#include <iterator>
#include <sstream>

namespace mortified {
    class DefaultStyleSheet :
        public StyleSheet
    {
    public:
        void updateStyles(std::string const *names, int nameCount,
                          std::string const *bases, int baseCount,
                          WidgetStyle const *style, StyleMask mask)
        {
            WidgetStyle tempStyle;
            StyleMask tempMask;
            for (int i = 0; i < baseCount; ++i) {
                MaskedStyle const &source = styles_[bases[i]];
                copy(&source.style, &source.mask, &tempStyle, &tempMask);
            }
            copy(style, &mask, &tempStyle, &tempMask);
            for (int i = 0; i < nameCount; ++i) {
                MaskedStyle &target = styles_[names[i]];
                copy(&tempStyle, &tempMask, &target.style, &target.mask);
            }
        }

        std::auto_ptr<WidgetStyle>
            applyStyles(std::string const *names, int nameCount)
        {
            std::auto_ptr<WidgetStyle> style(new WidgetStyle);
            for (int i = 0; i < nameCount; ++i) {
                MaskedStyle const &source = styles_[names[i]];
                copy(&source.style, &source.mask, style.get());
            }
            return style;
        }

    private:
        class MaskedStyle {
        public:
            WidgetStyle style;
            StyleMask mask;
        };

        typedef std::map<std::string, MaskedStyle> StyleMap;

        StyleMap styles_;

        void copy(WidgetStyle const *sourceStyle, StyleMask const *sourceMask,
                  WidgetStyle *targetStyle, StyleMask *targetMask = 0)
        {
            if (sourceMask->weight) {
                targetStyle->weight = sourceStyle->weight;
            }
            if (sourceMask->stretch) {
                targetStyle->stretch = sourceStyle->stretch;
            }
            if (sourceMask->alignment) {
                targetStyle->alignment = sourceStyle->alignment;
            }

            if (sourceMask->padding) {
                targetStyle->padding = sourceStyle->padding;
            }
            if (sourceMask->border) {
                targetStyle->border = sourceStyle->border;
            }
            if (sourceMask->spacing) {
                targetStyle->spacing = sourceStyle->spacing;
            }

            if (sourceMask->color) {
                targetStyle->color = sourceStyle->color;
            }
            if (sourceMask->backgroundColor) {
                targetStyle->backgroundColor = sourceStyle->backgroundColor;
            }
            if (sourceMask->borderColor) {
                targetStyle->borderColor = sourceStyle->borderColor;
            }

            if (targetMask) {
                targetMask->weight = sourceMask->weight;
                targetMask->stretch = sourceMask->stretch;
                targetMask->alignment = sourceMask->alignment;

                targetMask->padding = sourceMask->padding;
                targetMask->border = sourceMask->border;
                targetMask->spacing = sourceMask->spacing;

                targetMask->color = sourceMask->color;
                targetMask->backgroundColor = sourceMask->backgroundColor;
                targetMask->borderColor = sourceMask->borderColor;
            }
        }
    };

    std::auto_ptr<StyleSheet> createStyleSheet()
    {
        return std::auto_ptr<StyleSheet>(new DefaultStyleSheet);
    }
}
