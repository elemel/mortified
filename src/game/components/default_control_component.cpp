#include "default_control_component.hpp"

#include "character_stand_state.hpp"
#include "character_walk_state.hpp"
#include "control_component.hpp"
#include "control_service.hpp"
#include "game.hpp"
#include "actor.hpp"
#include "state.hpp"
#include "xml.hpp"

#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace mortified {
    class State;

    class DefaultControlComponent : public virtual ControlComponent {
    public:
        class StateData {
        public:
            State *state;
            ControlService::UpdateHandlerIterator updateHandler;

            StateData() :
                state(0)
            { }
        };

        explicit DefaultControlComponent(Actor *actor) :
            actor_(actor),
            controlService_(actor->game()->controlService())
        { }

        ~DefaultControlComponent()
        {
            while (!states_.empty()) {
                states_.back().state->leave();
                controlService_->removeUpdateHandler(states_.back().updateHandler);
                delete states_.back().state;
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
        Actor *actor_;
        ControlService *controlService_;
        std::vector<StateData> states_;

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
                std::auto_ptr<State> state = createState(stateRef);
                StateData *data = &*states_.insert(states_.end(), StateData());
                data->state = state.release();
                ControlService::UpdateHandler handler =
                    boost::bind(&DefaultControlComponent::updateStateMachine,
                                this, data, _1);
                data->updateHandler = controlService_->addUpdateHandler(handler);
                data->state->enter();
            }
        }
        
        void saveStateMachines(rapidxml::xml_node<> *parent)
        {
            for (std::size_t i = 0; i < states_.size(); ++i) {
                saveStateMachine(parent, states_[i].state);
            }
        }

        void saveStateMachine(rapidxml::xml_node<> *parent, State *state)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "state-machine");
            saveString(node, "state-ref", state->name());
        }

        void updateStateMachine(StateData *data, float dt)
        {
            data->state->update(dt);
            char const *name = data->state->transition();
            if (name) {
                std::auto_ptr<State> newState = createState(name);
                data->state->leave();
                std::auto_ptr<State> oldState(data->state);
                data->state = newState.release();
                data->state->enter();
                std::cerr << name << std::endl;
            }
        }

        std::auto_ptr<State> createState(char const *name)
        {
            if (std::strcmp(name, "character-stand") == 0) {
                return createCharacterStandState(actor_);
            }
            if (std::strcmp(name, "character-walk") == 0) {
                return createCharacterWalkState(actor_);
            }
            throw std::runtime_error(std::string("Failed to create state \"") +
                                     name + "\".");
        }        
    };

    std::auto_ptr<ControlComponent> createControlComponent(Actor *actor)
    {
        return std::auto_ptr<ControlComponent>(new DefaultControlComponent(actor));
    }
}
