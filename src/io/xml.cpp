#include "xml.hpp"

#include <cstdlib>

namespace mortified {
    bool loadBool(XmlNode *node)
    {
        return std::strcmp(node->value(), "true") == 0;
    }
    
    int loadInt(XmlNode *node)
    {
        return std::atoi(node->value());
    }
    
    float loadFloat(XmlNode *node)
    {
        return float(std::atof(node->value()));
    }
    
    Vector2 loadVector2(XmlNode *node)
    {
        Vector2 result;
        for (XmlNode *childNode = node->first_node(); childNode;
             childNode = childNode->next_sibling())
        {
            if (childNode->type() == rapidxml::node_element) {
                if (std::strcmp(childNode->name(), "x") == 0) {
                    result.x = loadFloat(childNode);
                }
                if (std::strcmp(childNode->name(), "y") == 0) {
                    result.y = loadFloat(childNode);
                }
            }
        }
        return result;
    }
    
    XmlNode *saveGroup(XmlNode *parentNode, char const *name)
    {
        XmlDocument *document = parentNode->document();
        rapidxml::xml_node<> *node =
        document->allocate_node(rapidxml::node_element,
                                document->allocate_string(name));
        parentNode->append_node(node);
        return node;
    }
    
    void saveString(XmlNode *parentNode, char const *name, char const *value)
    {
        XmlDocument *document = parentNode->document();
        XmlNode *node =
            document->allocate_node(rapidxml::node_element,
                                    name ? document->allocate_string(name) : 0,
                                    value ? document->allocate_string(value) : 0);
        parentNode->append_node(node);
    }
    
    void saveBool(XmlNode *parentNode, char const *name, bool b)
    {
        saveString(parentNode, name, b ? "true" : "false");
    }
    
    void saveInt(XmlNode *parentNode, char const *name, int i)
    {
        char buffer[32];
        std::sprintf(buffer, "%d", i);
        saveString(parentNode, name, buffer);
    }
    
    void saveFloat(XmlNode *parentNode, char const *name, float f)
    {
        char buffer[32];
        std::sprintf(buffer, "%g", f);
        saveString(parentNode, name, buffer);
    }
}
