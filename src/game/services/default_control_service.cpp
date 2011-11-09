#include "default_control_service.hpp"

#include "character_fall_state.hpp"
#include "character_jump_state.hpp"
#include "character_stand_state.hpp"
#include "character_walk_state.hpp"
#include "control_service.hpp"
#include "state.hpp"

#include <stdexcept>

namespace mortified {
    class DefaultControlService : public virtual ControlService {
    public:
        void load(rapidxml::xml_node<> *node)
        { }

        void save(rapidxml::xml_node<> *parent)
        { }

        void update(float dt)
        {
            for (UpdateHandlerIterator i = handlers_.begin();
                 i != handlers_.end(); ++i)
            {
                (*i)(dt);
            }
        }

        UpdateHandlerIterator addUpdateHandler(UpdateHandler handler)
        {
            return handlers_.insert(handlers_.end(), handler);
        }
        
        void removeUpdateHandler(UpdateHandlerIterator handler)
        {
            handlers_.erase(handler);
        }

        std::auto_ptr<State> createState(char const *name, Actor *actor)
        {
            if (std::strcmp(name, "character-fall") == 0) {
                return createCharacterFallState(actor);
            }
            if (std::strcmp(name, "character-jump") == 0) {
                return createCharacterJumpState(actor);
            }
            if (std::strcmp(name, "character-stand") == 0) {
                return createCharacterStandState(actor);
            }
            if (std::strcmp(name, "character-walk") == 0) {
                return createCharacterWalkState(actor);
            }
            throw std::runtime_error(std::string("Failed to create state \"") +
                                     name + "\".");
        }        

    private:
        UpdateHandlerList handlers_;
    };
    
    std::auto_ptr<ControlService> createControlService()
    {
        return std::auto_ptr<ControlService>(new DefaultControlService);
    }
}
