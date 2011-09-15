#ifndef MORTIFIED_STATE_HPP
#define MORTIFIED_STATE_HPP

#include <memory>

namespace mortified {
    class State {
    public:
        virtual ~State()
        { }

        virtual void enter() = 0;
        virtual void leave() = 0;

        virtual std::auto_ptr<State> transition() = 0;
    };
}

#endif
