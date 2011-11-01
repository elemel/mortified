#ifndef MORTIFIED_PROPERTY_SERVICE_HPP
#define MORTIFIED_PROPERTY_SERVICE_HPP

#include "service.hpp"

namespace mortified {
    class Type;

    class PropertyService : public virtual Service {
    public:
        virtual Type validateProperty(char const *name) const = 0;
    };
}

#endif
