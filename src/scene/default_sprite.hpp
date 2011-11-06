#ifndef MORTIFIED_DEFAULT_SPRITE_HPP
#define MORTIFIED_DEFAULT_SPRITE_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Sprite;
    class Texture;

    boost::intrusive_ptr<Sprite>
    createSprite(boost::intrusive_ptr<Texture> texture);
}

#endif
