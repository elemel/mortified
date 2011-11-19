#include "default_context.hpp"

#include "context.hpp"
#include "default_frame_buffer.hpp"
#include "default_texture.hpp"
#include "frame_buffer.hpp"
#include "graphics_resource_base.hpp"
#include "texture.hpp"
#include "texture_source.hpp"

#include <iostream>
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
        
        Context *asContext()
        {
            return this;
        }

        Context const *asContext() const
        {
            return this;
        }

        boost::intrusive_ptr<Texture>
        createTexture(boost::intrusive_ptr<TextureSource> source)
        {
            return mortified::createTexture(this, source);
        }

        boost::intrusive_ptr<Texture> createTexture(int width, int height)
        {
            return mortified::createTexture(this, width, height);
        }

        boost::intrusive_ptr<FrameBuffer> createFrameBuffer()
        {
            return mortified::createFrameBuffer(this);
        }
        
    private:
        SDL_Window *window_;
        SDL_GLContext context_;

        void createImpl()
        {
            context_ = SDL_GL_CreateContext(window_);
            if (SDL_GL_SetSwapInterval(1) == -1) {
                std::cerr << "WARNING: Failed to enable vertical sync: "
                          << SDL_GetError() << std::endl;
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

    boost::intrusive_ptr<Context>
    createContext(SDL_Window *window)
    {
        return boost::intrusive_ptr<Context>(new DefaultContext(window));
    }
}
