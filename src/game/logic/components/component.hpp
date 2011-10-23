#ifndef MORTIFIED_COMPONENT_HPP
#define MORTIFIED_COMPONENT_HPP

#include <rapidxml.hpp>

namespace mortified {
    class Component {
    public:
        virtual ~Component()
        { }

        virtual void load(rapidxml::xml_node<> *node) = 0;
        virtual void save(rapidxml::xml_node<> *parent) = 0;
    };
}

#endif
