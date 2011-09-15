#include "default_canvas_widget.hpp"

#include "canvas_widget.hpp"
#include "widget_base.hpp"

namespace mortified {
    class DefaultCanvasWidget :
        public virtual CanvasWidget,
        private virtual WidgetBase
    {
    public:
        void draw()
        {
            drawBackground();
            for (std::list<DrawHandler>::iterator i = drawHandlers_.begin();
                 i != drawHandlers_.end(); ++i)
            {
                (*i)();
            }
            drawBorder();
        }

        DrawHandlerIterator addDrawHandler(DrawHandler handler)
        {
            return drawHandlers_.insert(drawHandlers_.end(), handler);
        }

        void removeDrawHandler(DrawHandlerIterator iterator)
        {
            drawHandlers_.erase(iterator);
        }

        CanvasWidget *asCanvasWidget()
        {
            return this;
        }

        CanvasWidget const *asCanvasWidget() const
        {
            return this;
        }

    private:
        std::list<DrawHandler> drawHandlers_;
    };

    std::auto_ptr<Widget> createCanvasWidget()
    {
        return std::auto_ptr<Widget>(new DefaultCanvasWidget);
    }
}
