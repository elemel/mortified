#ifndef MORTIFIED_CANVAS_WIDGET_HPP
#define MORTIFIED_CANVAS_WIDGET_HPP

#include "widget.hpp"

namespace mortified {
    class CanvasWidget : public virtual Widget {
    public:
        typedef boost::function<void ()> DrawHandler;
        typedef std::list<DrawHandler>::iterator DrawHandlerIterator;

        virtual DrawHandlerIterator addDrawHandler(DrawHandler handler) = 0;
        virtual void removeDrawHandler(DrawHandlerIterator iterator) = 0;
    };
}

#endif
