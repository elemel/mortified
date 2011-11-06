#include "default_layout_parser.hpp"

#include "column_widget.hpp"
#include "context.hpp"
#include "default_canvas_widget.hpp"
#include "default_text_widget.hpp"
#include "layout_parser.hpp"
#include "row_widget.hpp"
#include "stream.hpp"
#include "text_widget.hpp"
#include "widget.hpp"

#include <rapidxml.hpp>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace mortified {
    class DefaultLayoutParser : public virtual LayoutParser {
    public:
        explicit DefaultLayoutParser(boost::intrusive_ptr<Context> context) :
            context_(context)
        { }
        
        std::auto_ptr<Widget> parse(Stream *stream)
        {
            int size = stream->seek(0, RW_SEEK_END);
            stream->seek(0, RW_SEEK_SET);
            std::vector<char> buffer(size + 1);
            stream->read(&buffer[0], size);
            buffer.back() = 0;

            rapidxml::xml_document<> document;
            document.parse<0>(&buffer[0]);

            return parseNode(document.first_node());
        }

    private:
        std::auto_ptr<Widget> parseNode(rapidxml::xml_node<> *node)
        {
            switch (node->type()) {
            case rapidxml::node_element:
                return parseElement(node);

            case rapidxml::node_data:
            case rapidxml::node_cdata:
            default:
                return std::auto_ptr<Widget>();
            }
        }

        std::auto_ptr<Widget> parseElement(rapidxml::xml_node<> *element)
        {
            std::auto_ptr<Widget> widget;
            if (strcmp(element->name(), "canvas") == 0) {
                widget = createCanvasWidget();
            } else if (strcmp(element->name(), "column") == 0) {
                widget = createColumnWidget();
            } else if (strcmp(element->name(), "row") == 0) {
                widget = createRowWidget();
            } else if (strcmp(element->name(), "text") == 0) {
                widget = createTextWidget(context_);
                if (TextWidget *textWidget = widget->asTextWidget()) {
                    textWidget->text(element->value());
                }
            }

            if (widget.get()) {
                if (rapidxml::xml_attribute<> *name = element->first_attribute("name")) {
                    widget->name(name->value());
                }
            }

            for (rapidxml::xml_node<> *childNode = element->first_node();
                 childNode; childNode = childNode->next_sibling())
            {
                std::auto_ptr<Widget> childWidget = parseNode(childNode);
                if (childWidget.get()) {
                    if (widget.get()) {
                        widget->addChild(childWidget);
                    } else {
                        return childWidget;
                    }
                }
            }

            return widget;
        }

    private:
        boost::intrusive_ptr<Context> context_;
    };

    std::auto_ptr<LayoutParser> createLayoutParser(boost::intrusive_ptr<Context> context)
    {
        return std::auto_ptr<LayoutParser>(new DefaultLayoutParser(context));
    }
}
