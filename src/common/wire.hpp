#ifndef MORTIFIED_WIRE_HPP
#define MORTIFIED_WIRE_HPP

#include <stdexcept>

namespace mortified {
    template <typename T>
    T *wire(T *ptr)
    {
        if (ptr == 0) {
            // TODO: Add class WireException, and throw that instead.
            throw std::runtime_error("Failed to wire null pointer.");
        }
        return ptr;
    }
}

#endif
