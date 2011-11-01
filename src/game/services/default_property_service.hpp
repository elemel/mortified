#ifndef MORTIFIED_DEFAULT_PROPERTY_SERVICE_HPP
#define MORTIFIED_DEFAULT_PROPERTY_SERVICE_HPP

#include <memory>

namespace mortified {
    class PropertyService;
    
    std::auto_ptr<PropertyService> createPropertyService();
}

#endif
