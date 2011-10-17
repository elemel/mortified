#ifndef MORTIFIED_XML_HPP
#define MORTIFIED_XML_HPP

#include <cstdlib>
#include <rapidxml.hpp>

namespace mortified {
    inline bool loadBool(rapidxml::xml_node<> *node)
    {
        return std::strcmp(node->value(), "true") == 0;
    }

    inline int loadInt(rapidxml::xml_node<> *node)
    {
        return std::atoi(node->value());
    }

    inline float loadFloat(rapidxml::xml_node<> *node)
    {
        return float(std::atof(node->value()));
    }

    inline rapidxml::xml_node<> *saveGroup(rapidxml::xml_node<> *parent,
                                           char const *name)
    {
        rapidxml::xml_document<> *document = parent->document();
        rapidxml::xml_node<> *node =
            document->allocate_node(rapidxml::node_element,
                                    document->allocate_string(name));
        parent->append_node(node);
        return node;
    }
    
    inline void saveString(rapidxml::xml_node<> *parent, char const *name,
                           char const *value)
    {
        rapidxml::xml_document<> *document = parent->document();
        rapidxml::xml_node<> *node =
            document->allocate_node(rapidxml::node_element,
                                    document->allocate_string(name),
                                    document->allocate_string(value));
        parent->append_node(node);
    }
    
    inline void saveBool(rapidxml::xml_node<> *parent, char const *name,
                         bool b)
    {
        saveString(parent, name, b ? "true" : "false");
    }

    inline void saveInt(rapidxml::xml_node<> *parent, char const *name, int i)
    {
        char buffer[32];
        std::sprintf(buffer, "%d", i);
        saveString(parent, name, buffer);
    }

    inline void saveFloat(rapidxml::xml_node<> *parent, char const *name,
                          float f)
    {
        char buffer[32];
        std::sprintf(buffer, "%g", f);
        saveString(parent, name, buffer);
    }
}

#endif
