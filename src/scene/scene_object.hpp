#ifndef MORTIFIED_SCENE_OBJECT_HPP
#define MORTIFIED_SCENE_OBJECT_HPP

#include "ref_counted.hpp"

namespace mortified {
    class SceneObject : public virtual RefCounted {
    public:
        virtual ~SceneObject()
        { }
        
        virtual void draw() = 0;
    };
}

#endif
