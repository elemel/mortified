#include "type.hpp"

#ifdef __GNUC__
#include <cxxabi.h>
#endif // __GNUC__

namespace mortified {
#ifdef __GNUC__
    namespace {
        struct ScopedFree {
            void *ptr;
            
            ScopedFree(void *ptr = 0) :
            ptr(ptr)
            { }
            
            ~ScopedFree()
            {
                if (ptr) {
                    free(ptr);
                }
            }
        };
    }
#endif // __GNUC__

    std::ostream &operator<<(std::ostream &out, Type const &type)
    {
#ifdef __GNUC__
        char const *name = type.info().name();
        int status = 0;
        char *demangledName = abi::__cxa_demangle(name, 0, 0, &status);
        if (demangledName) {
            ScopedFree scopedFree(demangledName);
            return out << demangledName;
        } else {
            return out << name;
        }
#else // __GNUC__
        return out << type.info().name();
#endif // __GNUC__
    }
}
