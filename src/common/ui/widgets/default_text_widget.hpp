#ifndef MORTIFIED_DEFAULT_TEXT_WIDGET_HPP
#define MORTIFIED_DEFAULT_TEXT_WIDGET_HPP

#include <memory>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class Context;
    class Widget;

    std::auto_ptr<Widget> createTextWidget(boost::shared_ptr<Context> context);
}

#endif
