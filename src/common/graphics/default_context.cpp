#include "default_context.hpp"

#include "context.hpp"
#include "default_texture.hpp"
#include "graphics_resource_base.hpp"
#include "texture.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultContext :
        public virtual Context,
        private virtual GraphicsResourceBase
    {
    public:
        explicit DefaultContext(SDL_Window *window) :
            window_(window),
            context_(0)
        { }

        ~DefaultContext()
        {
            if (context_) {
                SDL_GL_DeleteContext(context_);
            }
        }

        bool exists() const
        {
            return context_ != 0;
        }
        
        void createImpl()
        {
            context_ = SDL_GL_CreateContext(window_);
        }

        void destroyImpl()
        {
            SDL_GL_DeleteContext(context_);
            context_ = 0;
        }

        void invalidateImpl()
        {
            context_ = 0;
        }

        Context *asContext()
        {
            return this;
        }

        Context const *asContext() const
        {
            return this;
        }

        boost::intrusive_ptr<Texture>
            createTexture(boost::shared_ptr<TextureSource> source)
        {
            return mortified::createTexture(this, source);
        }

    private:
        SDL_Window *window_;
        SDL_GLContext context_;
    };

    boost::intrusive_ptr<Context> createContext(SDL_Window *window)
    {
        return new DefaultContext(window);
    }
}
