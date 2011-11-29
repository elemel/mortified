#ifndef MORTIFIED_DEFAULT_SOUND_COMPONENT_HPP
#define MORTIFIED_DEFAULT_SOUND_COMPONENT_HPP

#include <memory>

namespace mortified {
    class Actor;
    class SoundComponent;

    std::auto_ptr<SoundComponent> createSoundComponent(Actor *actor);
}

#endif
