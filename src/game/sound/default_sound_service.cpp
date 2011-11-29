#include "default_sound_service.hpp"

#include "sound_service.hpp"

#include <stdexcept>
#include <SDL/SDL_mixer.h>

namespace mortified {
    class DefaultSoundService : public virtual SoundService {
    public:
        DefaultSoundService() :
            dripSound_(0),
            dripChannel_(-1)
        {
            dripSound_ = Mix_LoadWAV("../../../data/sounds/drip.ogg");
            if (dripSound_) {
                dripChannel_ = Mix_PlayChannel(-1, dripSound_, -1);
            } else {
                std::string message = std::string("Failed to load sound: ") + Mix_GetError();
                throw std::runtime_error(message);
            }
        }

        ~DefaultSoundService()
        {
            if (dripChannel_ != -1) {
                Mix_HaltChannel(dripChannel_);
            }
            if (dripSound_) {
                Mix_FreeChunk(dripSound_);
            }            
        }

        void load(rapidxml::xml_node<> *node)
        { }
        
        void save(rapidxml::xml_node<> *parent)
        { }

        void update(float dt)
        { }

    private:
        Mix_Chunk *dripSound_;
        int dripChannel_;
    };

    std::auto_ptr<SoundService> createSoundService()
    {
        return std::auto_ptr<SoundService>(new DefaultSoundService);
    }
}
