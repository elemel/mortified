#ifndef MORTIFIED_DEFAULT_TEXT_WIDGET_HPP
#define MORTIFIED_DEFAULT_TEXT_WIDGET_HPP

#include <memory>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Widget;

    std::auto_ptr<Widget>
    createTextWidget(boost::intrusive_ptr<Context> context);
}

#endif
