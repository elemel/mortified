#ifndef MORTIFIED_STREAM_EXCEPTION_HPP
#define MORTIFIED_STREAM_EXCEPTION_HPP

#include <exception>
#include <string>

namespace mortified {
    class StreamException :
        public std::exception
    {
    public:
        explicit StreamException(const char *what) :
            what_(what)
        { }

        ~StreamException() throw ()
        { }

        const char *what() const throw ()
        {
            return what_.c_str();
        }

    private:
        std::string what_;
    };
}

#endif
