#ifndef MORTIFIED_DEFAULT_FONT_HPP
#define MORTIFIED_DEFAULT_FONT_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Font;
    class Stream;

    boost::intrusive_ptr<Font> createFont(Stream *stream, int fontSize);
}

#endif
