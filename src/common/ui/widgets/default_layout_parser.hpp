#ifndef MORTIFIED_DEFAULT_LAYOUT_PARSER_HPP
#define MORTIFIED_DEFAULT_LAYOUT_PARSER_HPP

#include <memory>

namespace mortified {
    class LayoutParser;

    std::auto_ptr<LayoutParser> createLayoutParser();
}

#endif
