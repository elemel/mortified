#ifndef MORTIFIED_FONT_HPP
#define MORTIFIED_FONT_HPP

#include <memory>

namespace mortified {
    class Image;

    class Font {
    public:
        virtual ~Font()
        { }

        virtual std::auto_ptr<Image> render(char const *text) = 0;
    };
}

#endif
