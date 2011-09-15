#ifndef MORTIFIED_UPDATE_HANDLER_HPP
#define MORTIFIED_UPDATE_HANDLER_HPP

namespace mortified {
    class UpdateHandler {
    public:
        virtual ~UpdateHandler()
        { }

        virtual void update(float dt) = 0;
    };
}

#endif
