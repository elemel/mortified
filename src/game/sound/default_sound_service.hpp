#ifndef MORTIFIED_DEFAULT_SOUND_SERVICE_HPP
#define MORTIFIED_DEFAULT_SOUND_SERVICE_HPP

#include <memory>

namespace mortified {
    class Context;
    class SoundService;

    std::auto_ptr<SoundService> createSoundService();
}

#endif
