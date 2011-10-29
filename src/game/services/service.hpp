#ifndef MORTIFIED_SERVICE_HPP
#define MORTIFIED_SERVICE_HPP

namespace mortified {
    class Service {
    public:
        virtual ~Service()
        { }

        virtual void update(float dt) = 0;
    };
}

#endif
