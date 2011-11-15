#ifndef MORTIFIED_DEFAULT_RENDER_SERVICE_HPP
#define MORTIFIED_DEFAULT_RENDER_SERVICE_HPP

#include <boost/intrusive_ptr.hpp>
#include <memory>

namespace mortified {
    class Context;
    class RenderService;

    std::auto_ptr<RenderService>
    createRenderService(boost::intrusive_ptr<Context> context);
}

#endif
