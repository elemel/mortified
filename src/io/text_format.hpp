#ifndef MORTIFIED_TEXT_FORMAT_HPP
#define MORTIFIED_TEXT_FORMAT_HPP

#include <cassert>

namespace mortified {
    class Stream;

    class TextFormat {
    public:
        explicit TextFormat(Stream *stream) :
            stream_(stream)
        {
            assert(stream);
        }

        Stream *stream() const
        {
            return stream_;
        }

    private:
        Stream *stream_;
    };

    TextFormat operator<<(TextFormat left, bool right);
    TextFormat operator<<(TextFormat left, int right);
    TextFormat operator<<(TextFormat left, float right);
    TextFormat operator<<(TextFormat left, char right);
    TextFormat operator<<(TextFormat left, char const *right);
}

#endif
