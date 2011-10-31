#include "default_control_component.hpp"

#include "character_stand_state.hpp"
#include "control_component.hpp"
#include "control_service.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "state.hpp"
#include "xml.hpp"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class State;

    class DefaultControlComponent : public virtual ControlComponent {
    public:
        typedef boost::shared_ptr<State> StatePtr;

        class StateData {
        public:
            StatePtr state;
            ControlService::UpdateHandlerIterator updateHandler;
        };

        typedef std::list<StateData> StateList;
        typedef StateList::iterator StateIterator;

        explicit DefaultControlComponent(GameObject *object) :
            object_(object),
            controlService_(object->game()->controlService())
        { }

        ~DefaultControlComponent()
        {
            while (!states_.empty()) {
                states_.back().state->leave();
                controlService_->removeUpdateHandler(states_.back().updateHandler);
                states_.pop_back();
            }
        }

        void load(rapidxml::xml_node<> *node)
        {
            loadStateMachines(node);
        }
        
        void save(rapidxml::xml_node<> *parent)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "control-component");
            saveStateMachines(node);
        }

    private:
        GameObject *object_;
        ControlService *controlService_;
        StateList states_;

        void loadStateMachines(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "state-machine") == 0) {
                        loadStateMachine(child);
                    }
                }
            }
        }

        void loadStateMachine(rapidxml::xml_node<> *node)
        {
            char const *stateRef = 0;
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "state-ref") == 0) {
                        stateRef = child->value();
                    }
                }
            }
            if (stateRef) {
                StatePtr state = StatePtr(createState(stateRef));
                StateData *data = &*states_.insert(states_.end(), StateData());
                data->state = state;
                ControlService::UpdateHandler handler =
                    boost::bind(&DefaultControlComponent::updateStateMachine,
                                this, data, _1);
                data->updateHandler = controlService_->addUpdateHandler(handler);
                state->enter();
            }
        }
        
        void saveStateMachines(rapidxml::xml_node<> *parent)
        { }
        
        void updateStateMachine(StateData *data, float dt)
        {
            data->state->update(dt);
            StatePtr newState = StatePtr(data->state->transition());
            if (newState) {
                data->state->leave();
                data->state = newState;
                data->state->enter();
            }
        }

        std::auto_ptr<State> createState(char const *name)
        {
            if (std::strcmp(name, "character-stand") == 0) {
                return createCharacterStandState(object_);
            }
            throw std::runtime_error(std::string("Failed to create state \"") +
                                     name + "\".");
        }        
    };

    std::auto_ptr<ControlComponent> createControlComponent(GameObject *object)
    {
        return std::auto_ptr<ControlComponent>(new DefaultControlComponent(object));
    }
}
