#include "default_property_component.hpp"

#include "game.hpp"
#include "actor.hpp"
#include "property_component.hpp"
#include "property_service.hpp"
#include "xml.hpp"

#include <stdexcept>
#include <vector>
#include <boost/variant.hpp>
#include <elemel/type.hpp>

namespace mortified {
    class DefaultPropertyComponent : public virtual PropertyComponent {
    public:
        typedef boost::variant<boost::blank, bool, int, float, elemel::string_ptr>
            PropertyValue;
        typedef std::pair<char const *, PropertyValue> PropertyPair;
        typedef std::vector<PropertyPair> PropertyVector;
        typedef PropertyVector::iterator PropertyIterator;

        explicit DefaultPropertyComponent(Actor *actor) :
            actor_(actor),
            propertyService_(actor->getGame()->getPropertyService())
        { }

        void load(rapidxml::xml_node<> *node)
        {
            loadProperties(node);
        }

        void save(rapidxml::xml_node<> *parent)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "property-component");
            saveProperties(node);
        }

        bool *findBool(char const *name)
        {
            return findAs<bool>(name);
        }

        int *findInt(char const *name)
        {
            return findAs<int>(name);
        }

        float *findFloat(char const *name)
        {
            return findAs<float>(name);
        }

        elemel::string_ptr *findString(char const *name)
        {
            return findAs<elemel::string_ptr>(name);
        }

    private:
        Actor *actor_;
        PropertyService *propertyService_;
        PropertyVector properties_;

        void loadProperties(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "property") == 0) {
                        loadProperty(child);
                    }
                }
            }
        }

        void loadProperty(rapidxml::xml_node<> *node)
        {
            char const *name = 0;
            rapidxml::xml_node<> *valueNode = 0;
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "name") == 0) {
                        name = child->value();
                    }
                    if (std::strcmp(child->name(), "value") == 0) {
                        valueNode = child;
                    }
                }
            }
            if (name && valueNode) {
                PropertyService::PropertyPair def = propertyService_->findProperty(name);
                if (def.first == 0) {
                    throw std::runtime_error(std::string("No property named \"") + name + "\".");
                }
                PropertyValue value;
                if (def.second == typeid(bool)) {
                    value = loadBool(valueNode);
                }
                if (def.second == typeid(int)) {
                    value = loadInt(valueNode);
                }
                if (def.second == typeid(float)) {
                    value = loadFloat(valueNode);
                }
                if (def.second == typeid(elemel::string_ptr)) {
                    value = elemel::string_ptr(valueNode->value());
                }
                properties_.push_back(PropertyPair(def.first, value));
            }
        }

        void saveProperties(rapidxml::xml_node<> *parent)
        {
            for (PropertyIterator i = properties_.begin();
                 i != properties_.end(); ++i)
            {
                rapidxml::xml_node<> *node = saveGroup(parent, "property");
                saveProperty(node, &*i);
            }
        }

        void saveProperty(rapidxml::xml_node<> *parent, PropertyPair const *property)
        {
            saveString(parent, "name", property->first);
            bool const *b = boost::get<bool>(&property->second);
            int const *i = boost::get<int>(&property->second);
            float const *f = boost::get<float>(&property->second);
            elemel::string_ptr const *s = boost::get<elemel::string_ptr>(&property->second);
            if (b) {
                saveBool(parent, "value", *b);
            }
            if (i) {
                saveInt(parent, "value", *i);
            }
            if (f) {
                saveFloat(parent, "value", *f);
            }
            if (s) {
                saveString(parent, "value", s->data());
            }
        }

        template <typename T>
        T *findAs(char const *name)
        {
            PropertyValue *value = find(name);
            if (value == 0) {
                return 0;
            }
            T *result = boost::get<T>(value);
            if (result == 0) {
                throw std::runtime_error(std::string("Wrong type for property \"") + name + "\".");
            }
            return result;
        }

        PropertyValue *find(char const *name)
        {
            for (PropertyIterator i = properties_.begin();
                 i != properties_.end(); ++i)
            {
                if (std::strcmp(i->first, name) == 0) {
                    return &i->second;
                }
            }
            return 0;
        }
    };

    std::auto_ptr<PropertyComponent> createPropertyComponent(Actor *actor)
    {
        return std::auto_ptr<PropertyComponent>(new DefaultPropertyComponent(actor));
    }
}
