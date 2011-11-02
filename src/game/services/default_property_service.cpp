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

        DefaultPropertyService()
        {
            // TODO: Load config from XML.
            properties_["left-input"] = typeid(bool);
            properties_["right-input"] = typeid(bool);
            properties_["jump-input"] = typeid(bool);
        }

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
    };
    
    std::auto_ptr<PropertyService> createPropertyService()
    {
        return std::auto_ptr<PropertyService>(new DefaultPropertyService);
    }
}
