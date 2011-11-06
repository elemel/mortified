#ifndef MORTIFIED_STREAM_HPP
#define MORTIFIED_STREAM_HPP

#include <SDL/SDL_rwops.h>

namespace mortified {
    class Stream {
    public:
        virtual ~Stream()
        { }

        virtual int seek(int offset, int whence) = 0;
        virtual int read(void *target, int size) = 0;
        virtual int write(void const *source, int size) = 0;

        virtual SDL_RWops *rwops() = 0;
    };
}

#endif
