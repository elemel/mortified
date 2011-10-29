#ifndef MORTIFIED_WIDGET_HPP
#define MORTIFIED_WIDGET_HPP

#include "widget_style.hpp"

#include <list>
#include <memory>
#include <boost/function.hpp>
#include <SDL/SDL_events.h>

namespace mortified {
    class CanvasWidget;
    class TextWidget;

    class Widget {
    public:
        typedef boost::function<bool (SDL_Event const *event)>
            EventHandler;
        typedef std::list<EventHandler>::iterator EventHandlerIterator;

        virtual ~Widget()
        { }

        virtual char const *type() const = 0;

        virtual char const *name() const = 0;
        virtual void name(char const *name) = 0;

        virtual Widget *parent() = 0;
        virtual Widget const *parent() const = 0;
        virtual void parent(Widget *parent) = 0;

        virtual int childCount() const = 0;
        virtual Widget *child(int index) = 0;
        virtual Widget const *child(int index) const = 0;
        virtual void addChild(std::auto_ptr<Widget> child) = 0;
        virtual std::auto_ptr<Widget> removeChild(Widget *child) = 0;

        virtual WidgetStyle const *style() const = 0;
        virtual void style(WidgetStyle const *style) = 0;

        virtual WidgetPosition position() const = 0;
        virtual void position(WidgetPosition position) = 0;

        virtual WidgetSize size() const = 0;
        virtual void size(WidgetSize size) = 0;

        virtual WidgetSize minSize() const = 0;

        virtual void measure() = 0;
        virtual void arrange() = 0;
        virtual void draw() = 0;

        virtual bool handleEvent(SDL_Event const *event) = 0;

        virtual EventHandlerIterator addEventHandler(EventHandler handler) = 0;
        virtual void removeEventHandler(EventHandlerIterator iterator) = 0;

        virtual WidgetPosition
            toAbsolutePosition(WidgetPosition relativePosition) const = 0;
        virtual WidgetPosition
            toRelativePosition(WidgetPosition absolutePosition) const = 0;

        virtual CanvasWidget *asCanvasWidget() = 0;
        virtual CanvasWidget const *asCanvasWidget() const = 0;

        virtual TextWidget *asTextWidget() = 0;
        virtual TextWidget const *asTextWidget() const = 0;
    };
}

#endif
