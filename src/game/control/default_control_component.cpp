#include "default_control_component.hpp"

#include "actor.hpp"
#include "control_component.hpp"
#include "control_service.hpp"
#include "game.hpp"
#include "math.hpp"
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
            controlService_(actor->getGame()->getControlService())
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

        void load(rapidxml::xml_node<> *node, Matrix3 transform)
        {
            loadStateMachines(node);
        }
        
        void save(rapidxml::xml_node<> *parent, Matrix3 transform)
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
                std::auto_ptr<State> state =
                    controlService_->createState(stateRef, actor_);
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
            saveString(node, "state-ref", state->getName());
        }

        void updateStateMachine(StateData *data, float dt)
        {
            data->state->update(dt);
            char const *name = data->state->transition();
            if (name) {
                std::auto_ptr<State> newState =
                    controlService_->createState(name, actor_);
                data->state->leave();
                std::auto_ptr<State> oldState(data->state);
                data->state = newState.release();
                data->state->enter();
                std::cerr << name << std::endl;
            }
        }
    };

    std::auto_ptr<ControlComponent> createControlComponent(Actor *actor)
    {
        return std::auto_ptr<ControlComponent>(new DefaultControlComponent(actor));
    }
}
