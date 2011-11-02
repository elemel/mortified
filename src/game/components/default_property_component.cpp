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
            propertyService_(actor->game()->propertyService())
        { }

        void load(rapidxml::xml_node<> *node)
        {
            loadProperties(node);
        }

        void save(rapidxml::xml_node<> *parent)
        { }

        bool *bindBool(char const *name)
        {
            return bind<bool>(name);
        }

        int *bindInt(char const *name)
        {
            return bind<int>(name);
        }

        float *bindFloat(char const *name)
        {
            return bind<float>(name);
        }

        elemel::string_ptr *bindString(char const *name)
        {
            return bind<elemel::string_ptr>(name);
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
                properties_.push_back(PropertyPair(name, value));
            }
        }

        template <typename T>
        T *bind(char const *name)
        {
            PropertyIterator found = properties_.end();
            for (PropertyIterator i = properties_.begin();
                 i != properties_.end(); ++i)
            {
                if (std::strcmp(i->first, name) == 0) {
                    found = i;
                    break;
                }
            }
            if (found == properties_.end()) {
                throw std::runtime_error(std::string("No property named \"") + name + "\".");
            }
            T *result = boost::get<T>(&found->second);
            if (result == 0) {
                throw std::runtime_error(std::string("Wrong type for property \"") + name + "\".");
            }
            return result;
        }
    };

    std::auto_ptr<PropertyComponent> createPropertyComponent(Actor *actor)
    {
        return std::auto_ptr<PropertyComponent>(new DefaultPropertyComponent(actor));
    }
}
