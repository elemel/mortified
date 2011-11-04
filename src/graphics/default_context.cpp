#include "default_context.hpp"

#include "context.hpp"
#include "default_texture.hpp"
#include "graphics_resource_base.hpp"
#include "texture.hpp"

#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultContext :
        public virtual Context,
        public virtual boost::enable_shared_from_this<DefaultContext>,
        private virtual GraphicsResourceBase
    {
    public:
        explicit DefaultContext(SDL_Window *window, bool multisample) :
            window_(window),
            multisample_(multisample),
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
        
        Context *asContext()
        {
            return this;
        }

        Context const *asContext() const
        {
            return this;
        }

        boost::shared_ptr<Texture>
        createTexture(boost::shared_ptr<TextureSource> source)
        {
            return mortified::createTexture(shared_from_this(), source);
        }

        boost::shared_ptr<Texture> createTexture(int width, int height)
        {
            return mortified::createTexture(shared_from_this(), width, height);
        }

    private:
        SDL_Window *window_;
        bool multisample_;
        SDL_GLContext context_;

        void createImpl()
        {
            context_ = SDL_GL_CreateContext(window_);
            if (SDL_GL_SetSwapInterval(1) == -1) {
                std::cerr << "WARNING: Failed to enable vertical sync: "
                << SDL_GetError() << std::endl;
            }
            if (multisample_) {
                glEnable(GL_MULTISAMPLE);
            }
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
    };

    boost::shared_ptr<Context>
    createContext(SDL_Window *window, bool multisample)
    {
        return boost::shared_ptr<Context>(new DefaultContext(window, multisample));
    }
}
