#ifndef MORTIFIED_EDITOR_SCENE_OBJECT_BASE_HPP
#define MORTIFIED_EDITOR_SCENE_OBJECT_BASE_HPP

#include "editor_scene_object.hpp"

namespace mortified {
    class EditorSceneObjectBase : public virtual EditorSceneObject {
    public:
        EditorScene *scene()
        {
            return scene_;
        }

        EditorScene const *scene() const
        {
            return scene_;
        }

        void scene(EditorScene *scene)
        {
            scene_ = scene;
        }

        void draw()
        { }

    private:
        EditorScene *scene_;
    };
}

#endif
