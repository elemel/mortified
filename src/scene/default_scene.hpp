#ifndef MORTIFIED_DEFAULT_SCENE_HPP
#define MORTIFIED_DEFAULT_SCENE_HPP

#include <boost/intrusive_ptr.hpp>

#include <memory>

namespace mortified {
    class Context;
    class Scene;

    std::auto_ptr<Scene> createScene(boost::intrusive_ptr<Context> context);
}

#endif
