#ifndef MORTIFIED_DEFAULT_SPRITE_HPP
#define MORTIFIED_DEFAULT_SPRITE_HPP

#include <boost/shared_ptr.hpp>

namespace mortified {
    class Sprite;
    class Texture;

    boost::shared_ptr<Sprite> createSprite(boost::shared_ptr<Texture> texture);
}

#endif
