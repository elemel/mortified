#ifndef MORTIFIED_EDITOR_SCENE_OBJECT_HPP
#define MORTIFIED_EDITOR_SCENE_OBJECT_HPP

namespace mortified {
    class EditorScene;

    class EditorSceneObject {
    public:
        virtual ~EditorSceneObject()
        { }

        virtual EditorScene *scene() = 0;
        virtual EditorScene const *scene() const = 0;
        virtual void scene(EditorScene *scene) = 0;

        virtual void draw() = 0;
    };
}

#endif
