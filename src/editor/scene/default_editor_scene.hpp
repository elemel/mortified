#ifndef MORTIFIED_DEFAULT_EDITOR_SCENE_HPP
#define MORTIFIED_DEFAULT_EDITOR_SCENE_HPP

#include <memory>

namespace mortified {
    class EditorScene;

    std::auto_ptr<EditorScene> createEditorScene();
}

#endif
