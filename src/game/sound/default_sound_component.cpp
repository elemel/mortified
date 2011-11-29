#include "default_sound_component.hpp"

#include "actor.hpp"
#include "game.hpp"
#include "sound_component.hpp"
#include "sound_service.hpp"
#include "xml.hpp"

namespace mortified {
    class DefaultSoundComponent : public virtual SoundComponent {
    public:
        explicit DefaultSoundComponent(Actor *actor) :
            actor_(actor),
            soundService_(actor->getGame()->getSoundService())
        { }

        void load(XmlNode *node, Matrix3 parentTransform)
        { }
        
        void save(XmlNode *parentNode, Matrix3 parentTransform)
        {
            rapidxml::xml_node<> *node = saveGroup(parentNode, "sound-component");
            (void) node;
        }
        
        void draw()
        { }

    private:
        Actor *actor_;
        SoundService *soundService_;
    };

    std::auto_ptr<SoundComponent> createSoundComponent(Actor *actor)
    {
        return std::auto_ptr<SoundComponent>(new DefaultSoundComponent(actor));
    }
}
