#ifndef MORTIFIED_DEFAULT_LAYOUT_PARSER_HPP
#define MORTIFIED_DEFAULT_LAYOUT_PARSER_HPP

#include <memory>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class LayoutParser;

    std::auto_ptr<LayoutParser>
    createLayoutParser(boost::intrusive_ptr<Context> context);
}

#endif
