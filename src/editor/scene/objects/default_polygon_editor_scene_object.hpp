#ifndef MORTIFIED_DEFAULT_POLYGON_EDITOR_SCENE_OBJECT_HPP
#define MORTIFIED_DEFAULT_POLYGON_EDITOR_SCENE_OBJECT_HPP

#include <memory>

namespace mortified {
    class EditorSceneObject;

    std::auto_ptr<EditorSceneObject> createPolygonEditorSceneObject();
}

#endif
