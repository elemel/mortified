#ifndef MORTIFIED_WIDGET_STYLE_HPP
#define MORTIFIED_WIDGET_STYLE_HPP

namespace mortified {
    class WidgetPosition {
    public:
        int x;
        int y;

        WidgetPosition();
        WidgetPosition(int x, int y);
    };

    inline WidgetPosition::WidgetPosition() :
        x(0),
        y(0)
    { }

    inline WidgetPosition::WidgetPosition(int x, int y) :
        x(x),
        y(y)
    { }

    class WidgetSize {
    public:
        int width;
        int height;

        explicit WidgetSize(int size = 0);
        WidgetSize(int width, int height);
    };

    inline WidgetSize::WidgetSize(int size) :
        width(size),
        height(size)
    { }

    inline WidgetSize::WidgetSize(int width, int height) :
        width(width),
        height(height)
    { }

    class WidgetBox {
    public:
        WidgetPosition position;
        WidgetSize size;

        WidgetBox();
        WidgetBox(WidgetPosition position, WidgetSize size);
    };

    inline WidgetBox::WidgetBox()
    { }

    inline WidgetBox::WidgetBox(WidgetPosition position, WidgetSize size) :
        position(position),
        size(size)
    { }

    class WidgetWeight {
    public:
        float horizontal;
        float vertical;

        explicit WidgetWeight(float weight = 0.0f);
        WidgetWeight(float horizontal, float vertical);
    };

    inline WidgetWeight::WidgetWeight(float weight) :
        horizontal(weight),
        vertical(weight)
    { }

    inline WidgetWeight::WidgetWeight(float horizontal, float vertical) :
        horizontal(horizontal),
        vertical(vertical)
    { }

    class WidgetStretch {
    public:
        float horizontal;
        float vertical;

        explicit WidgetStretch(float stretch = 0.0f);
        WidgetStretch(float horizontal, float vertical);
    };

    inline WidgetStretch::WidgetStretch(float stretch) :
        horizontal(stretch),
        vertical(stretch)
    { }

    inline WidgetStretch::WidgetStretch(float horizontal, float vertical) :
        horizontal(horizontal),
        vertical(vertical)
    { }

    class WidgetAlignment {
    public:
        float horizontal;
        float vertical;

        explicit WidgetAlignment(float alignment = 0.0f);
        WidgetAlignment(float horizontal, float vertical);
    };

    inline WidgetAlignment::WidgetAlignment(float alignment) :
        horizontal(alignment),
        vertical(alignment)
    { }

    inline WidgetAlignment::WidgetAlignment(float horizontal, float vertical) :
        horizontal(horizontal),
        vertical(vertical)
    { }

    class WidgetPadding {
    public:
        int left;
        int top;
        int right;
        int bottom;

        explicit WidgetPadding(int padding = 0);
        WidgetPadding(int horizontal, int vertical);
        WidgetPadding(int left, int top, int right, int bottom);
    };

    inline WidgetPadding::WidgetPadding(int padding) :
        left(padding),
        top(padding),
        right(padding),
        bottom(padding)
    { }

    inline WidgetPadding::WidgetPadding(int horizontal, int vertical) :
        left(horizontal),
        top(vertical),
        right(horizontal),
        bottom(vertical)
    { }

    inline WidgetPadding::WidgetPadding(int left, int top, int right,
                                        int bottom) :
        left(left),
        top(top),
        right(right),
        bottom(bottom)
    { }

    class WidgetBorder {
    public:
        int left;
        int top;
        int right;
        int bottom;

        explicit WidgetBorder(int border = 0);
        WidgetBorder(int horizontal, int vertical);
        WidgetBorder(int left, int top, int right, int bottom);
    };

    inline WidgetBorder::WidgetBorder(int border) :
        left(border),
        top(border),
        right(border),
        bottom(border)
    { }

    inline WidgetBorder::WidgetBorder(int horizontal, int vertical) :
        left(horizontal),
        top(vertical),
        right(horizontal),
        bottom(vertical)
    { }

    inline WidgetBorder::WidgetBorder(int left, int top, int right,
                                      int bottom) :
        left(left),
        top(top),
        right(right),
        bottom(bottom)
    { }

    class WidgetSpacing {
    public:
        int horizontal;
        int vertical;

        explicit WidgetSpacing(int spacing = 0);
        WidgetSpacing(int horizontal, int vertical);
    };

    inline WidgetSpacing::WidgetSpacing(int spacing) :
        horizontal(spacing),
        vertical(spacing)
    { }

    inline WidgetSpacing::WidgetSpacing(int horizontal, int vertical) :
        horizontal(horizontal),
        vertical(vertical)
    { }

    class WidgetColor {
    public:
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char alpha;

        explicit WidgetColor(unsigned char color = 255,
                             unsigned char alpha = 255);
        WidgetColor(unsigned char red, unsigned char green, unsigned char blue,
                    unsigned char alpha = 255);
    };

    inline WidgetColor::WidgetColor(unsigned char color,
                                    unsigned char alpha) :
        red(color),
        green(color),
        blue(color),
        alpha(alpha)
    { }

    inline WidgetColor::WidgetColor(unsigned char red, unsigned char green,
                                    unsigned char blue, unsigned char alpha)
    :
        red(red),
        green(green),
        blue(blue),
        alpha(alpha)
    { }

    class WidgetStyle {
    public:
        WidgetWeight weight;
        WidgetStretch stretch;
        WidgetAlignment alignment;

        WidgetPadding padding;
        WidgetBorder border;
        WidgetSpacing spacing;

        WidgetColor color;
        WidgetColor backgroundColor;
        WidgetColor borderColor;

        WidgetStyle() :
            weight(0.0f),
            stretch(0.0f),
            alignment(0.0f),
    
            color(0),
            backgroundColor(255),
            borderColor(0)
        { }
    };
}

#endif
