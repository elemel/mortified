#include "default_sound_service.hpp"

#include "sound_service.hpp"

namespace mortified {
    class DefaultSoundService : public virtual SoundService {
    public:
        DefaultSoundService()
        { }

        void load(rapidxml::xml_node<> *node)
        { }
        
        void save(rapidxml::xml_node<> *parent)
        { }

        void update(float dt)
        { }
    };

    std::auto_ptr<SoundService> createSoundService()
    {
        return std::auto_ptr<SoundService>(new DefaultSoundService);
    }
}
