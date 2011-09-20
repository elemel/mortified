#ifndef MORTIFIED_FONT_HPP
#define MORTIFIED_FONT_HPP

#include <boost/shared_ptr.hpp>

namespace mortified {
    class Image;

    class Font {
    public:
        virtual ~Font()
        { }

        virtual boost::shared_ptr<Image> render(char const *text) = 0;
    };
}

#endif
