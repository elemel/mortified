#ifndef MORTIFIED_DEFAULT_CANVAS_WIDGET_HPP
#define MORTIFIED_DEFAULT_CANVAS_WIDGET_HPP

#include <memory>

namespace mortified {
    class Widget;

    std::auto_ptr<Widget> createCanvasWidget();
}

#endif
