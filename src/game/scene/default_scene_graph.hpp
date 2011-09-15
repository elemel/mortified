#ifndef MORTIFIED_DEFAULT_SCENE_GRAPH_HPP
#define MORTIFIED_DEFAULT_SCENE_GRAPH_HPP

#include <memory>

namespace mortified {
    class SceneGraph;

    std::auto_ptr<SceneGraph> createSceneGraph();
}

#endif
