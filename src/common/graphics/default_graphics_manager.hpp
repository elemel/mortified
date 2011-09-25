#ifndef MORTIFIED_DEFAULT_GRAPHICS_MANAGER_HPP
#define MORTIFIED_DEFAULT_GRAPHICS_MANAGER_HPP

#include <boost/shared_ptr.hpp>

namespace mortified {
    class GraphicsManager;
    
    boost::shared_ptr<GraphicsManager> createGraphicsManager();
}

#endif
