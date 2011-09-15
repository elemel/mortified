#include "default_editor_scene.hpp"

#include "editor_scene.hpp"
#include "editor_scene_object.hpp"

namespace mortified {
    class DefaultEditorScene : public virtual EditorScene {
    public:
        ~DefaultEditorScene()
        {
            while (!objects_.empty()) {
                delete objects_.back();
                objects_.pop_back();
            }
        }

        ObjectIterator addObject(std::auto_ptr<EditorSceneObject> object)
        {
            ObjectIterator result = objects_.insert(objects_.end(), 0);
            objects_.back() = object.release();
            return result;
        }

        std::auto_ptr<EditorSceneObject> removeObject(ObjectIterator object)
        {
            std::auto_ptr<EditorSceneObject> result(*object);
            objects_.erase(object);
            return result;
        }

        ObjectRange objects()
        {
            return ObjectRange(objects_.begin(), objects_.end());
        }

        ConstObjectRange objects() const
        {
            return ConstObjectRange(objects_.begin(), objects_.end());
        }

        void draw()
        {
            for (ObjectIterator i = objects_.begin(); i != objects_.end(); ++i)
            {
                (*i)->draw();
            }
        }

    private:
        std::list<EditorSceneObject *> objects_;
    };

    std::auto_ptr<EditorScene> createEditorScene()
    {
        return std::auto_ptr<EditorScene>(new DefaultEditorScene);
    }
}
