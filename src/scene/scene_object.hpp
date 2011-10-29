#ifndef MORTIFIED_SCENE_OBJECT_HPP
#define MORTIFIED_SCENE_OBJECT_HPP

namespace mortified {
    class SceneObject {
    public:
        virtual ~SceneObject()
        { }
        
        virtual void draw() = 0;
    };
}

#endif
