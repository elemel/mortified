#ifndef MORTIFIED_SERVICE_HPP
#define MORTIFIED_SERVICE_HPP

#include <rapidxml.hpp>

namespace mortified {
    class Service {
    public:
        virtual ~Service()
        { }

        virtual void load(rapidxml::xml_node<> *node) = 0;
        virtual void save(rapidxml::xml_node<> *parent) = 0;

        virtual void update(float dt) = 0;
    };
}

#endif
