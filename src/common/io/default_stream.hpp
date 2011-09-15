#ifndef MORTIFIED_DEFAULT_STREAM_HPP
#define MORTIFIED_DEFAULT_STREAM_HPP

#include <memory>

namespace mortified {
    class Stream;

    std::auto_ptr<Stream>
        createStreamFromFile(const char *file, const char *mode);
}

#endif
