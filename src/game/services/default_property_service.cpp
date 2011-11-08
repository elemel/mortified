#include "default_property_service.hpp"

#include "property_service.hpp"

#include <map>
#include <stdexcept>
#include <string>
#include <elemel/const_string.hpp>

namespace mortified {
    class DefaultPropertyService : public virtual PropertyService {
    public:
        typedef std::map<elemel::const_string, elemel::type> PropertyMap;
        typedef PropertyMap::const_iterator ConstPropertyIterator;

        void load(rapidxml::xml_node<> *node)
        {
            loadProperties(node);
        }
        
        void save(rapidxml::xml_node<> *parent)
        { }

        void update(float dt)
        { }

        PropertyPair findProperty(char const *name) const
        {
            elemel::const_string key(name, elemel::by_ref);
            ConstPropertyIterator i = properties_.find(key);
            if (i == properties_.end()) {
                return PropertyPair(0, elemel::type());
            }
            return PropertyPair(i->first.data(), i->second);
        }

    private:
        PropertyMap properties_;

        void loadProperties(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (strcmp(child->name(), "property") == 0) {
                        loadProperty(child);
                    }
                }
            }
        }

        void loadProperty(rapidxml::xml_node<> *node)
        {
            char const *name = 0;
            elemel::type type;
            for (rapidxml::xml_node<> *child = node->first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (strcmp(child->name(), "name") == 0) {
                        name = child->value();
                    }
                }
                if (child->type() == rapidxml::node_element) {
                    if (strcmp(child->name(), "type") == 0) {
                        type = loadType(child);
                    }
                }
            }
            if (name && type != typeid(void)) {
                properties_[name] = type;
            }
        }

        elemel::type loadType(rapidxml::xml_node<> *node)
        {
            char const *name = node->value();
            if (strcmp(name, "bool") == 0) {
                return typeid(bool);
            }
            if (strcmp(name, "int") == 0) {
                return typeid(int);
            }
            if (strcmp(name, "float") == 0) {
                return typeid(float);
            }
            if (strcmp(name, "string") == 0) {
                return typeid(elemel::string_ptr);
            }
            throw std::runtime_error(std::string("Failed to parse \"") + name + "\" as type.");
        }
    };
    
    std::auto_ptr<PropertyService> createPropertyService()
    {
        return std::auto_ptr<PropertyService>(new DefaultPropertyService);
    }
}
