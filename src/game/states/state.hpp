#ifndef MORTIFIED_STATE_HPP
#define MORTIFIED_STATE_HPP

namespace mortified {
    class State {
    public:
        virtual ~State()
        { }

        virtual char const *name() const = 0;

        virtual void enter() = 0;
        virtual void leave() = 0;

        virtual void update(float dt) = 0;
        virtual char const *transition() = 0;
    };
}

#endif
