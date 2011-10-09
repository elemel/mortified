#ifndef MORTIFIED_SCENE_HPP
#define MORTIFIED_SCENE_HPP

#include <list>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class SceneObject;

    class Scene {
    public:
        typedef boost::shared_ptr<SceneObject> ObjectPtr;
        typedef std::list<ObjectPtr> ObjectList;
        typedef ObjectList::iterator ObjectIterator;

        virtual ~Scene()
        { }

        virtual ObjectIterator addObject(ObjectPtr object) = 0;
        virtual void removeObject(ObjectIterator object) = 0;

        virtual void update(float dt) = 0;
        virtual void draw() = 0;
    };
}

#endif
