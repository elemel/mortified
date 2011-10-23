#ifndef MORTIFIED_DEFAULT_GRAPHICS_SERVICE_HPP
#define MORTIFIED_DEFAULT_GRAPHICS_SERVICE_HPP

#include <memory>

namespace mortified {
    class GraphicsService;

    std::auto_ptr<GraphicsService> createGraphicsService();
}

#endif
