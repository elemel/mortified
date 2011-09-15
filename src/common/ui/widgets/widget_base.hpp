#ifndef MORTIFIED_WIDGET_BASE_HPP
#define MORTIFIED_WIDGET_BASE_HPP

#include "widget.hpp"

#include <cassert>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace mortified {
    class WidgetBase :
        public virtual Widget
    {
    public:
        WidgetBase() :
            parent_(0)
        { }

        ~WidgetBase()
        {
            while (!children_.empty()) {
                delete children_.back();
                children_.pop_back();
            }
        }

        char const *type() const
        {
            return "widget";
        }

        char const *name() const
        {
            return name_.c_str();
        }

        void name(char const *name)
        {
            name_ = name;
        }

        Widget *parent()
        {
            return parent_;
        }

        Widget const *parent() const
        {
            return parent_;
        }

        void parent(Widget *parent)
        {
            parent_ = parent;
        }

        int childCount() const
        {
            return int(children_.size());
        }

        Widget *child(int index)
        {
            assert(index >= 0 && index < int(children_.size()));
            return children_[index];
        }

        Widget const *child(int index) const
        {
            assert(index >= 0 && index < int(children_.size()));
            return children_[index];
        }

        void addChild(std::auto_ptr<Widget> child);
        std::auto_ptr<Widget> removeChild(Widget *child);

        WidgetStyle const *style() const
        {
            return &style_;
        }

        void style(WidgetStyle const *style)
        {
            assert(style);
            style_ = *style;
        }

        WidgetPosition position() const
        {
            return position_;
        }

        void position(WidgetPosition position)
        {
            position_ = position;
        }

        WidgetSize size() const
        {
            return size_;
        }

        void size(WidgetSize size)
        {
            size_ = size;
        }

        WidgetSize minSize() const;

        void measure();
        void arrange();
        void draw();

        bool handleEvent(SDL_Event const *event);

        EventHandlerIterator addEventHandler(EventHandler handler)
        {
            return eventHandlers_.insert(eventHandlers_.end(), handler);
        }

        void removeEventHandler(EventHandlerIterator iterator)
        {
            eventHandlers_.erase(iterator);
        }

        WidgetPosition toAbsolutePosition(WidgetPosition relativePosition) const;
        WidgetPosition toRelativePosition(WidgetPosition absolutePosition) const;

        CanvasWidget *asCanvasWidget()
        {
            return 0;
        }

        CanvasWidget const *asCanvasWidget() const
        {
            return 0;
        }

        TextWidget *asTextWidget()
        {
            return 0;
        }

        TextWidget const *asTextWidget() const
        {
            return 0;
        }

    protected:
        std::string name_;

        Widget *parent_;
        std::vector<Widget *> children_;

        WidgetStyle style_;

        WidgetPosition position_;
        WidgetSize size_;
        WidgetSize minContentSize_;

        std::list<EventHandler> eventHandlers_;

        void measureChildren();
        void arrangeChildren();

        WidgetPosition minContentPosition() const;
        WidgetSize maxContentSize() const;

        int stretch(int inner, int outer, float stretch) const;
        int align(int inner, int outer, float alignment) const;

        void drawBackground();
        void drawBorder();
        void drawChildren();
        void drawBox(int x, int y, int width, int height);
    };
}

#endif
