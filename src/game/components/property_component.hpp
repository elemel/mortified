#ifndef MORTIFIED_PROPERTY_COMPONENT_HPP
#define MORTIFIED_PROPERTY_COMPONENT_HPP

#include "component.hpp"

#include <string>

namespace mortified {
    class PropertyComponent : public virtual Component {
    public:
        virtual bool *bindBool(char const *name) = 0;
        virtual int *bindInt(char const *name) = 0;
        virtual float *bindFloat(char const *name) = 0;
        virtual std::string *bindString(char const *name) = 0;
    };
}

#endif
