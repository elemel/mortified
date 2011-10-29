#ifndef MORTIFIED_COLOR_HPP
#define MORTIFIED_COLOR_HPP

namespace mortified {
    class Color3 {
    public:
        unsigned char red;
        unsigned char green;
        unsigned char blue;

        Color3();
        Color3(unsigned char red, unsigned char green, unsigned char blue);
    };

    inline Color3::Color3() :
        red(255),
        green(255),
        blue(255)
    { }

    inline Color3::Color3(unsigned char red, unsigned char green,
                          unsigned char blue) :
        red(red),
        green(green),
        blue(blue)
    { }

    class Color4 {
    public:
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char alpha;

        Color4();
        Color4(unsigned char red, unsigned char green, unsigned char blue,
               unsigned char alpha = 255);
    };

    inline Color4::Color4() :
        red(255),
        green(255),
        blue(255),
        alpha(255)
    { }

    inline Color4::Color4(unsigned char red, unsigned char green,
                          unsigned char blue, unsigned char alpha) :
        red(red),
        green(green),
        blue(blue),
        alpha(alpha)
    { }
}

#endif
