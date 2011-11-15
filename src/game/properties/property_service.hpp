#ifndef MORTIFIED_PROPERTY_SERVICE_HPP
#define MORTIFIED_PROPERTY_SERVICE_HPP

#include "service.hpp"

#include <elemel/string_ptr.hpp>
#include <elemel/type.hpp>

namespace mortified {
    class PropertyService : public virtual Service {
    public:
        typedef std::pair<char const *, elemel::type> PropertyPair;

        virtual PropertyPair findProperty(char const *name) const = 0;
    };
}

#endif
