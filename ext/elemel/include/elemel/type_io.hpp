#ifndef ELEMEL_TYPE_IO_HPP
#define ELEMEL_TYPE_IO_HPP

#include <iostream>

#ifdef __GNUC__
#include <cxxabi.h>
#endif // __GNUC__

namespace elemel {
    template <class C, class T>
    std::basic_ostream<C, T> &
    operator<<(std::basic_ostream<C, T> &out, type const &t)
    {
#ifdef __GNUC__
        char const *name = t.info().name();
        int status = 0;
        char *demangled = abi::__cxa_demangle(name, 0, 0, &status);
        if (demangled) {
            try {
                out << demangled;
                free(demangled);
                return out;
            } catch (...) {
                free(demangled);
                throw;
            }
        } else {
            return out << name;
        }
#else // __GNUC__
        return out << t.info().name();
#endif // __GNUC__
    }
}

#endif // ELEMEL_TYPE_IO_HPP
