#ifndef MORTIFIED_DEFAULT_FONT_HPP
#define MORTIFIED_DEFAULT_FONT_HPP

#include <memory>

namespace mortified {
    class Font;
    class Stream;

    std::auto_ptr<Font> createFont(Stream *stream, int fontSize);
}

#endif
