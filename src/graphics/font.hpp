#ifndef MORTIFIED_FONT_HPP
#define MORTIFIED_FONT_HPP

#include "ref_counted.hpp"

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Image;

    class Font : public virtual RefCounted {
    public:
        virtual ~Font()
        { }

        virtual boost::intrusive_ptr<Image> render(char const *text) = 0;
    };
}

#endif
