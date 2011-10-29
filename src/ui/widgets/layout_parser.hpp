#ifndef MORTIFIED_LAYOUT_PARSER_HPP
#define MORTIFIED_LAYOUT_PARSER_HPP

#include <memory>

namespace mortified {
    class Stream;
    class Widget;

    class LayoutParser {
    public:
        virtual std::auto_ptr<Widget> parse(Stream *stream) = 0;
    };
}

#endif
