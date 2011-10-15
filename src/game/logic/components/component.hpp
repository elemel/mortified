#ifndef MORTIFIED_COMPONENT_HPP
#define MORTIFIED_COMPONENT_HPP

#include <rapidxml.hpp>

namespace mortified {
    class Component {
    public:
        virtual ~Component()
        { }

        virtual const char *type() const = 0;
        virtual void load(rapidxml::xml_node<> *node) = 0;
        virtual void save(rapidxml::xml_node<> *node) = 0;

        virtual void update(float dt) = 0;
    };
}

#endif
