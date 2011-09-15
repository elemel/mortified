#ifndef MORTIFIED_DEFAULT_STYLE_PARSER_HPP
#define MORTIFIED_DEFAULT_STYLE_PARSER_HPP

#include <memory>

namespace mortified {
    class StyleParser;

    std::auto_ptr<StyleParser> createStyleParser();
}

#endif
