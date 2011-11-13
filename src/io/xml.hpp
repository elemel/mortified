#ifndef MORTIFIED_XML_HPP
#define MORTIFIED_XML_HPP

#include "math.hpp"

#include <rapidxml.hpp>

namespace mortified {
    typedef rapidxml::xml_document<> XmlDocument;
    typedef rapidxml::xml_node<> XmlNode;

    bool loadBool(XmlNode *node);
    int loadInt(XmlNode *node);
    float loadFloat(XmlNode *node);
    Vector2 loadVector2(XmlNode *node);

    XmlNode *saveGroup(XmlNode *parentNode, char const *name);
    void saveString(XmlNode *parentNode, char const *name, char const *value);
    void saveBool(XmlNode *parentNode, char const *name, bool b);
    void saveInt(XmlNode *parentNode, char const *name, int i);
    void saveFloat(XmlNode *parentNode, char const *name, float f);
}

#endif
