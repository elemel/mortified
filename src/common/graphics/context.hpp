#ifndef MORTIFIED_CONTEXT_HPP
#define MORTIFIED_CONTEXT_HPP

namespace mortified {
    class Context {
    public:
        virtual ~Context()
        { }

        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual void invalidate() = 0;
    };
}

#endif
