#ifndef MORTIFIED_SPRITE_CONTROLLER_HPP
#define MORTIFIED_SPRITE_CONTROLLER_HPP

namespace mortified {
    class SpriteController {
    public:
        virtual ~SpriteController()
        { }

        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual void update() = 0;
    };
}

#endif
