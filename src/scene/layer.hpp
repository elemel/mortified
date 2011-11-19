#ifndef MORTIFIED_LAYER_HPP
#define MORTIFIED_LAYER_HPP

#include <list>
#include <boost/intrusive_ptr.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace mortified {
    class Sprite;
    
    class Layer {
    public:
        typedef boost::ptr_list<Sprite> SpriteList;
        typedef SpriteList::iterator SpriteIterator;
        typedef SpriteList::const_iterator ConstSpriteIterator;
        
        virtual ~Layer()
        { }

        virtual SpriteIterator createSprite(int layerIndex) = 0;
        virtual void destroySprite(SpriteIterator sprite) = 0;

        virtual void draw() = 0;
    };
}

#endif
