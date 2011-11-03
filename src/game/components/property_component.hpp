#ifndef MORTIFIED_PROPERTY_COMPONENT_HPP
#define MORTIFIED_PROPERTY_COMPONENT_HPP

#include "component.hpp"

#include <elemel/string_ptr.hpp>

namespace mortified {
    class PropertyComponent : public virtual Component {
    public:
        virtual bool *findBool(char const *name) = 0;
        virtual int *findInt(char const *name) = 0;
        virtual float *findFloat(char const *name) = 0;
        virtual elemel::string_ptr *findString(char const *name) = 0;
    };
}

#endif
