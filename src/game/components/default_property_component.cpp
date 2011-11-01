#include "default_property_component.hpp"

#include "game.hpp"
#include "game_object.hpp"
#include "property_component.hpp"
#include "property_service.hpp"
#include "type.hpp"
#include "xml.hpp"

#include <map>
#include <stdexcept>
#include <boost/variant.hpp>

namespace mortified {
    class DefaultPropertyComponent : public virtual PropertyComponent {
    public:
        typedef boost::variant<boost::blank, bool, int, float, std::string>
            PropertyValue;
        typedef std::map<std::string, PropertyValue> PropertyMap;
        typedef PropertyMap::iterator PropertyIterator;

        explicit DefaultPropertyComponent(GameObject *object) :
            object_(object),
            propertyService_(object->game()->propertyService())
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

        std::string *bindString(char const *name)
        {
            return bind<std::string>(name);
        }

    private:
        GameObject *object_;
        PropertyService *propertyService_;
        PropertyMap properties_;

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
                Type type = propertyService_->validateProperty(name);
                if (type == typeid(bool)) {
                    properties_[name] = loadBool(valueNode);
                }
                if (type == typeid(int)) {
                    properties_[name] = loadInt(valueNode);
                }
                if (type == typeid(float)) {
                    properties_[name] = loadFloat(valueNode);
                }
                if (type == typeid(std::string)) {
                    properties_[name] = std::string(valueNode->value());
                }
            }
        }

        template <typename T>
        T *bind(char const *name)
        {
            PropertyIterator i = properties_.find(name);
            if (i == properties_.end()) {
                throw std::runtime_error(std::string("No property named \"") + name + "\".");
            }
            T *result = boost::get<T>(&i->second);
            if (result == 0) {
                throw std::runtime_error(std::string("Wrong type for property \"") + name + "\".");
            }
            return result;
        }
    };

    std::auto_ptr<PropertyComponent> createPropertyComponent(GameObject *object)
    {
        return std::auto_ptr<PropertyComponent>(new DefaultPropertyComponent(object));
    }
}
