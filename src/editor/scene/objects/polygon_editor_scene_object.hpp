#ifndef MORTIFIED_POLYGON_EDITOR_SCENE_OBJECT_HPP
#define MORTIFIED_POLYGON_EDITOR_SCENE_OBJECT_HPP

#include "editor_scene_object.hpp"

namespace mortified {
    class Polygon2;

    class PolygonEditorSceneObject : public virtual EditorSceneObject {
    public:
        virtual Polygon2 *polygon() = 0;
        virtual Polygon2 const *polygon() const = 0;
    };
}

#endif
