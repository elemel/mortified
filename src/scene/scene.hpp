#ifndef MORTIFIED_SCENE_HPP
#define MORTIFIED_SCENE_HPP

#include <list>
#include <boost/intrusive_ptr.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace mortified {
    class Context;
    class Sprite;

    class Scene {
    public:
        typedef boost::ptr_list<Sprite> SpriteList;
        typedef SpriteList::iterator SpriteIterator;
        typedef SpriteList::const_iterator ConstSpriteIterator;

        virtual ~Scene()
        { }

        virtual boost::intrusive_ptr<Context> getContext() = 0;

        virtual SpriteIterator createSprite() = 0;
        virtual void destroySprite(SpriteIterator sprite) = 0;

        virtual void draw() = 0;
    };
}

#endif
