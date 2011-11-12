#ifndef MORTIFIED_COMPONENT_HPP
#define MORTIFIED_COMPONENT_HPP

#include <rapidxml.hpp>

namespace mortified {
    class Matrix3;

    class Component {
    public:
        virtual ~Component()
        { }

        virtual void load(rapidxml::xml_node<> *node, Matrix3 parentTransform) = 0;
        virtual void save(rapidxml::xml_node<> *parentNode, Matrix3 parentTransform) = 0;
    };
}

#endif
