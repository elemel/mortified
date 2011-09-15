#ifndef MORTIFIED_IMAGE_EDITOR_SCENE_OBJECT_HPP
#define MORTIFIED_IMAGE_EDITOR_SCENE_OBJECT_HPP

#include "editor_scene_object.hpp"

namespace mortified {
    class Image;

    class ImageEditorSceneObject : public virtual EditorSceneObject {
    public:
        virtual Image *image() = 0;
        virtual Image const *image() const = 0;
    };
}

#endif
