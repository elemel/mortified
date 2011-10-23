#ifndef MORTIFIED_SCENE_OBJECT_BASE_HPP
#define MORTIFIED_SCENE_OBJECT_BASE_HPP

#include "scene_object.hpp"

namespace mortified {
    class SceneObjectBase : public virtual SceneObject {
    public:
        void update(float dt)
        { }
        
        void draw()
        { }
    };
}

#endif
