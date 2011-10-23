#include "default_scene.hpp"

#include "scene.hpp"
#include "scene_object.hpp"

#include <cassert>
#include <iostream>
#include <vector>

namespace mortified {
    class DefaultScene :
        public virtual Scene
    {
    public:
        ObjectIterator addObject(ObjectPtr object)
        {
            return objects_.insert(objects_.end(), object);
        }

        void removeObject(ObjectIterator object)
        {
            objects_.erase(object);
        }

        void update(float dt)
        {
            for (ObjectIterator i = objects_.begin(); i != objects_.end(); ++i)
            {
                (*i)->update(dt);
            }
        }

        void draw()
        {
            for (ObjectIterator i = objects_.begin(); i != objects_.end(); ++i)
            {
                (*i)->draw();
            }
        }

    private:
        ObjectList objects_;
    };

    std::auto_ptr<Scene> createScene()
    {
        return std::auto_ptr<Scene>(new DefaultScene);
    }
}
