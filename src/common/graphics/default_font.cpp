#include "default_font.hpp"

#include "default_image.hpp"
#include "font.hpp"
#include "image.hpp"
#include "stream.hpp"

#include <SDL/SDL_ttf.h>

#include <cassert>
#include <stdexcept>

namespace mortified {
    class DefaultFont :
        public Font
    {
    public:
        explicit DefaultFont(TTF_Font *font) :
            font_(font)
        {
            assert(font);
        }

        ~DefaultFont()
        {
            TTF_CloseFont(font_);
        }

        std::auto_ptr<Image> render(char const *text)
        {
            assert(text);
            SDL_Color color = { 255, 255, 255, 255 };
            SDL_Surface *surface = TTF_RenderText_Blended(font_, text, color);
            if (surface == 0) {
                throw std::runtime_error(std::string("Failed to render text: ") +
                                         TTF_GetError());
            }
            std::auto_ptr<Image> image;
            try {
                image = createImage(surface);
                SDL_FreeSurface(surface);
            } catch (...) {
                SDL_FreeSurface(surface);
                throw;
            }
            return image;
        }

    private:
        TTF_Font *font_;
    };

    std::auto_ptr<Font> createFont(Stream *stream, int fontSize)
    {
        assert(stream);
        TTF_Font *font = TTF_OpenFontRW(stream->rwops(), 0, fontSize);
        if (font == 0) {
            throw std::runtime_error(std::string("Failed to load font: ") +
                                     TTF_GetError());
        }
        return std::auto_ptr<Font>(new DefaultFont(font));
    }
}
