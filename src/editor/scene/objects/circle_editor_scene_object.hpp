#ifndef MORTIFIED_CIRCLE_EDITOR_SCENE_OBJECT_HPP
#define MORTIFIED_CIRCLE_EDITOR_SCENE_OBJECT_HPP

#include "editor_scene_object.hpp"

namespace mortified {
    class Circle;

    class CircleEditorSceneObject : public virtual EditorSceneObject {
    public:
        virtual Circle2 *circle() = 0;
        virtual Circle2 const *circle() const = 0;
    };
}

#endif
