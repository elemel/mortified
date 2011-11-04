#ifndef MORTIFIED_WIRE_HPP
#define MORTIFIED_WIRE_HPP

#include <sstream>
#include <stdexcept>
#include <elemel/type.hpp>
#include <elemel/type_io.hpp>

namespace mortified {
    class WireException : public std::exception {
    public:
        explicit WireException(char const *message) :
            message_(message)
        { }

        explicit WireException(std::string const &message) :
            message_(message)
        { }

        ~WireException() throw ()
        { }

        char const *what() const throw ()
        {
            return message_.c_str();
        }

    private:
        std::string message_;
    };

    template <typename T>
    T *wire(T *ptr)
    {
        if (ptr == 0) {
            std::stringstream message;
            message << "Failed to wire null pointer of type \"" << elemel::type(typeid(T)) << "\".";
            throw WireException(message.str());
        }
        return ptr;
    }
}

#endif
