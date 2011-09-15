#include "text_format.hpp"

#include "stream.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>

namespace mortified {
    inline TextFormat operator<<(TextFormat left, bool right)
    {
        return left << (right ? "true" : "false");
    }

    inline TextFormat operator<<(TextFormat left, int right)
    {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%d", right);
        return left << buffer;
    }

    inline TextFormat operator<<(TextFormat left, float right)
    {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%g", double(right));
        return left << buffer;
    }

    inline TextFormat operator<<(TextFormat left, char right)
    {
        left.stream()->write(&right, 1);
        return left;
    }

    inline TextFormat operator<<(TextFormat left, char const *right)
    {
        assert(right);
        left.stream()->write(right, std::strlen(right));
        return left;
    }
}
