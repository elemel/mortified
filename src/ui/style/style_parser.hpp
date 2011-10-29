#ifndef MORTIFIED_STYLE_PARSER_HPP
#define MORTIFIED_STYLE_PARSER_HPP

#include <memory>

namespace mortified {
    class Stream;
    class StyleSheet;

    class StyleParser {
    public:
        virtual ~StyleParser()
        { }

        virtual std::auto_ptr<StyleSheet> parse(Stream *stream) = 0;
    };
}

#endif
