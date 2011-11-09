#ifndef MORTIFIED_DEFAULT_GRAPHICS_SERVICE_HPP
#define MORTIFIED_DEFAULT_GRAPHICS_SERVICE_HPP

#include <boost/intrusive_ptr.hpp>
#include <memory>

namespace mortified {
    class Context;
    class GraphicsService;

    std::auto_ptr<GraphicsService>
    createGraphicsService(boost::intrusive_ptr<Context> context);
}

#endif
