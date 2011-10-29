#include "widget_base.hpp"

#include <iostream>
#include <SDL/SDL_opengl.h>

namespace mortified {
    WidgetSize WidgetBase::minSize() const
    {
        return WidgetSize(style_.border.left + style_.padding.left +
                          minContentSize_.width +
                          style_.padding.right + style_.border.right,
                          style_.border.top + style_.padding.top +
                          minContentSize_.height +
                          style_.padding.bottom + style_.border.bottom);
    }

    void WidgetBase::addChild(std::auto_ptr<Widget> child)
    {
        assert(child.get() != 0);
        assert(child->parent() == 0);
        children_.push_back(child.get());
        child.release();
        children_.back()->parent(this);
    }

    std::auto_ptr<Widget> WidgetBase::removeChild(Widget *child)
    {
        std::vector<Widget *>::iterator i =
            std::find(children_.begin(), children_.end(), child);
        assert(i != children_.end());
        child->parent(0);
        children_.erase(i);
        return std::auto_ptr<Widget>(child);
    }

    void WidgetBase::measure()
    {
        measureChildren();
        minContentSize_ = WidgetSize();
    }

    void WidgetBase::measureChildren()
    {
        typedef std::vector<Widget *>::iterator Iterator;
        for (Iterator i = children_.begin(); i != children_.end(); ++i) {
            (*i)->measure();
        }
    }

    void WidgetBase::arrange()
    {
        arrangeChildren();
    }

    void WidgetBase::arrangeChildren()
    {
        typedef std::vector<Widget *>::iterator Iterator;
        for (Iterator i = children_.begin(); i != children_.end(); ++i) {
            (*i)->arrange();
        }
    }

    WidgetPosition WidgetBase::minContentPosition() const
    {
        return WidgetPosition(style_.border.left + style_.padding.left,
                              style_.border.top + style_.padding.top);
    }

    WidgetSize WidgetBase::maxContentSize() const
    {
        return WidgetSize(size_.width -
                          style_.border.left - style_.padding.left -
                          style_.padding.right - style_.border.right,
                          size_.height -
                          style_.border.top - style_.padding.top -
                          style_.padding.bottom - style_.border.bottom);
    }

    int WidgetBase::stretch(int inner, int outer, float stretch) const
    {
        return inner + int(stretch * (outer - inner) + 0.5f);
    }

    int WidgetBase::align(int inner, int outer, float alignment) const
    {
        return int(alignment * float(outer - inner) + 0.5f);
    }

    void WidgetBase::draw()
    {
        drawBackground();
        drawChildren();
        drawBorder();
    }

    void WidgetBase::drawBackground()
    {
        if (style_.backgroundColor.alpha && size_.width && size_.height) {
            glColor4ub(style_.backgroundColor.red,
                       style_.backgroundColor.green,
                       style_.backgroundColor.blue,
                       style_.backgroundColor.alpha);
            drawBox(position_.x, position_.y, size_.width, size_.height);
        }
    }

    void WidgetBase::drawBorder()
    {
        if (style_.borderColor.alpha &&
            (style_.border.left || style_.border.top ||
             style_.border.right || style_.border.bottom))
        {
            glColor4ub(style_.borderColor.red,
                       style_.borderColor.green,
                       style_.borderColor.blue,
                       style_.borderColor.alpha);
            if (style_.border.left) {
                drawBox(position_.x, position_.y + style_.border.top,
                        style_.border.left,
                        size_.height - style_.border.top -
                        style_.border.bottom);
            }
            if (style_.border.top) {
                drawBox(position_.x, position_.y, size_.width,
                        style_.border.top);
            }
            if (style_.border.right) {
                drawBox(position_.x + size_.width - style_.border.right,
                        position_.y + style_.border.top,
                        style_.border.right,
                        size_.height - style_.border.top -
                        style_.border.bottom);
            }
            if (style_.border.bottom) {
                drawBox(position_.x,
                        position_.y + size_.height - style_.border.bottom,
                        size_.width, style_.border.bottom);
            }
        }
    }

    void WidgetBase::drawChildren()
    {
        if (!children_.empty()) {
            glPushMatrix();
            glTranslatef(float(position_.x), float(position_.y), 0.0f);
            typedef std::vector<Widget *>::const_iterator Iterator;
            for (Iterator i = children_.begin(); i != children_.end(); ++i) {
                (*i)->draw();
            }
            glPopMatrix();
        }
    }

    void WidgetBase::drawBox(int x, int y, int width, int height)
    {
        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();
    }

    bool WidgetBase::handleEvent(SDL_Event const *event)
    {
        WidgetPosition mousePosition;
        switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            mousePosition.x = event->button.x;
            mousePosition.y = event->button.y;
            break;

        case SDL_MOUSEMOTION:
            mousePosition.x = event->motion.x;
            mousePosition.y = event->motion.y;
            break;
        }

        switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEMOTION:
            {
                typedef std::vector<Widget *>::iterator Iterator;
                for (Iterator i = children_.begin(); i != children_.end();
                     ++i)
                {
                    WidgetPosition childPosition =
                        (*i)->toAbsolutePosition((*i)->position());
                    WidgetSize childSize = (*i)->size();
                    if (childPosition.x <= mousePosition.x &&
                        mousePosition.x < childPosition.x + childSize.width &&
                        childPosition.y <= mousePosition.y &&
                        mousePosition.y < childPosition.y + childSize.height)
                    {
                        if ((*i)->handleEvent(event)) {
                            return true;
                        }
                    }
                }
            }
            break;
        }

        for (EventHandlerIterator i = eventHandlers_.begin();
             i != eventHandlers_.end(); ++i)
        {
            if ((*i)(event)) {
                return true;
            }
        }

        return false;
    }

    WidgetPosition
        WidgetBase::toAbsolutePosition(WidgetPosition relativePosition) const
    {
        int originX = 0;
        int originY = 0;
        for (Widget const *ancestor = parent_; ancestor;
             ancestor = ancestor->parent())
        {
            WidgetPosition ancestorPosition = ancestor->position();
            originX += ancestorPosition.x;
            originY += ancestorPosition.y;
        }
        return WidgetPosition(relativePosition.x + originX,
                              relativePosition.y + originY);
    }

    WidgetPosition
        WidgetBase::toRelativePosition(WidgetPosition absolutePosition) const
    {
        int originX = 0;
        int originY = 0;
        for (Widget const *ancestor = parent_; ancestor;
             ancestor = ancestor->parent())
        {
            WidgetPosition ancestorPosition = ancestor->position();
            originX += ancestorPosition.x;
            originY += ancestorPosition.y;
        }
        return WidgetPosition(absolutePosition.x - originX,
                              absolutePosition.y - originY);
    }
}
