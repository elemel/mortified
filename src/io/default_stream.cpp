#include "default_stream.hpp"

#include "stream_exception.hpp"
#include "stream.hpp"

#include <cassert>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace mortified {
    class DefaultStream :
        public Stream
    {
    public:
        explicit DefaultStream(SDL_RWops *rwops) :
            rwops_(rwops)
        { }

        ~DefaultStream()
        {
            SDL_RWclose(rwops_);
        }

        int seek(int offset, int whence)
        {
            return SDL_RWseek(rwops_, offset, whence);
        }

        int read(void *target, int size)
        {
            return SDL_RWread(rwops_, target, 1, size);
        }

        int write(void const *source, int size)
        {
            return SDL_RWwrite(rwops_, source, 1, size);
        }

        SDL_RWops *rwops()
        {
            return rwops_;
        }

    private:
        SDL_RWops *rwops_;
    };

    std::auto_ptr<Stream>
        createStreamFromFile(const char *file, const char *mode)
    {
        SDL_RWops *rwops = SDL_RWFromFile(file, mode);
        if (rwops == 0) {
            std::stringstream what;
            what << "Failed to open file \"" << file << "\": "
                 << SDL_GetError();
            throw StreamException(what.str().c_str());
        }
        return std::auto_ptr<Stream>(new DefaultStream(rwops));
    }
}
