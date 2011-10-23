#ifndef MORTIFIED_DEFAULT_SCENE_HPP
#define MORTIFIED_DEFAULT_SCENE_HPP

#include <memory>

namespace mortified {
    class Scene;

    std::auto_ptr<Scene> createScene();
}

#endif
