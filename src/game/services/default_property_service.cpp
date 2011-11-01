#include "default_property_service.hpp"

#include "property_service.hpp"
#include "type.hpp"

#include <stdexcept>
#include <string>

namespace mortified {
    class DefaultPropertyService : public virtual PropertyService {
    public:
        void update(float dt)
        { }

        Type validateProperty(char const *name) const
        {
            // TODO: Load property config from XML.
            if (std::strcmp(name, "left-input") == 0) {
                return typeid(bool);
            }
            if (std::strcmp(name, "right-input") == 0) {
                return typeid(bool);
            }
            if (std::strcmp(name, "jump-input") == 0) {
                return typeid(bool);
            }
            throw std::runtime_error(std::string("Invalid property name \"") +
                                     name + "\".");
        }
    };
    
    std::auto_ptr<PropertyService> createPropertyService()
    {
        return std::auto_ptr<PropertyService>(new DefaultPropertyService);
    }
}
