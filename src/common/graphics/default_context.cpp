#include "default_context.hpp"

#include "context.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultContext :
        public virtual Context
    {
    public:
        explicit DefaultContext(SDL_Window *window) :
            window_(window),
            context_(0)
        { }

        ~DefaultContext()
        {
            DefaultContext::destroy();
        }

        void create()
        {
            destroy();
            context_ = SDL_GL_CreateContext(window_);
        }

        void destroy()
        {
            if (context_) {
                SDL_GL_DeleteContext(context_);
                invalidate();
            }
        }

        void invalidate()
        {
            context_ = 0;
        }

    private:
        SDL_Window *window_;
        SDL_GLContext context_;
    };

    std::auto_ptr<Context> createContext(SDL_Window *window)
    {
        return std::auto_ptr<Context>(new DefaultContext(window));
    }
}
