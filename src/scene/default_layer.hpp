#ifndef MORTIFIED_DEFAULT_LAYER_HPP
#define MORTIFIED_DEFAULT_LAYER_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Layer;
    
    std::auto_ptr<Layer> createLayer(Scene *scene);
}

#endif
