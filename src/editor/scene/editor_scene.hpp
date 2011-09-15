#ifndef MORTIFIED_EDITOR_SCENE_HPP
#define MORTIFIED_EDITOR_SCENE_HPP

#include <list>
#include <utility>

namespace mortified {
    class EditorSceneObject;

    class EditorScene {
    public:
        typedef std::list<EditorSceneObject *>::iterator ObjectIterator;
        typedef std::list<EditorSceneObject *>::const_iterator
            ConstObjectIterator;
        typedef std::pair<ObjectIterator, ObjectIterator> ObjectRange;
        typedef std::pair<ConstObjectIterator, ConstObjectIterator>
            ConstObjectRange;

        virtual ~EditorScene()
        { }

        virtual ObjectIterator
            addObject(std::auto_ptr<EditorSceneObject> object) = 0;
        virtual std::auto_ptr<EditorSceneObject>
            removeObject(ObjectIterator object) = 0;
        virtual ObjectRange objects() = 0;
        virtual ConstObjectRange objects() const = 0;

        virtual void draw() = 0;
    };
}

#endif
