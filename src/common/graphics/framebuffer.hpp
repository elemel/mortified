#ifndef MORTIFIED_FRAMEBUFFER_HPP
#define MORTIFIED_FRAMEBUFFER_HPP

namespace mortified {
    class Framebuffer {
    public:
        virtual ~Framebuffer()
        { }

        virtual int width() const = 0;
        virtual int height() const = 0;

        virtual void create() = 0;
        virtual void invalidate() = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void draw() = 0;
    };
}

#endif
