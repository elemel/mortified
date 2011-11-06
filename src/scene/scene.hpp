#ifndef MORTIFIED_SCENE_HPP
#define MORTIFIED_SCENE_HPP

#include <list>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class SceneObject;

    class Scene {
    public:
        typedef boost::intrusive_ptr<SceneObject> ObjectPtr;
        typedef std::list<ObjectPtr> ObjectList;
        typedef ObjectList::iterator ObjectIterator;

        virtual ~Scene()
        { }

        virtual ObjectIterator addObject(ObjectPtr object) = 0;
        virtual void removeObject(ObjectIterator object) = 0;

        virtual void draw() = 0;
    };
}

#endif
