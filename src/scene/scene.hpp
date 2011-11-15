#ifndef MORTIFIED_SCENE_HPP
#define MORTIFIED_SCENE_HPP

#include <list>
#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Sprite;

    class Scene {
    public:
        typedef boost::intrusive_ptr<Sprite> SpritePtr;
        typedef std::list<SpritePtr> SpriteList;
        typedef SpriteList::iterator SpriteIterator;

        virtual ~Scene()
        { }

        virtual SpriteIterator addSprite(SpritePtr sprite) = 0;
        virtual void removeSprite(SpriteIterator sprite) = 0;

        virtual void draw() = 0;
    };
}

#endif
