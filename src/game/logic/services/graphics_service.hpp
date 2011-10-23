#ifndef MORTIFIED_GRAPHICS_SERVICE_HPP
#define MORTIFIED_GRAPHICS_SERVICE_HPP

#include "service.hpp"

namespace mortified {
    class Scene;

    class GraphicsService : public virtual Service {
    public:
        virtual ~GraphicsService()
        { }

        virtual Scene *scene() = 0;
    };
}

#endif
