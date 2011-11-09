#include "default_game.hpp"

#include "context.hpp"
#include "control_service.hpp"
#include "default_control_service.hpp"
#include "default_actor.hpp"
#include "default_graphics_service.hpp"
#include "default_physics_service.hpp"
#include "default_property_service.hpp"
#include "default_stream.hpp"
#include "game.hpp"
#include "actor.hpp"
#include "graphics_service.hpp"
#include "physics_service.hpp"
#include "property_service.hpp"
#include "stream.hpp"
#include "xml.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <Box2D/Box2D.h>

namespace mortified {
    class DefaultGame : public virtual Game {
    public:
        explicit DefaultGame(boost::intrusive_ptr<Context> context) :
            time_(0.0f),
            propertyService_(createPropertyService()),
            controlService_(createControlService()),
            physicsService_(createPhysicsService()),
            graphicsService_(createGraphicsService(context))
        { }
        
        ~DefaultGame()
        {
            while (!actors_.empty()) {
                delete actors_.back();
                actors_.pop_back();
            }
        }

        void loadConfig(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (strcmp(child->name(), "property-service") == 0) {
                        propertyService_->load(child);
                    }
                    if (strcmp(child->name(), "control-service") == 0) {
                        controlService_->load(child);
                    }
                    if (strcmp(child->name(), "physics-service") == 0) {
                        physicsService_->load(child);
                    }
                    if (strcmp(child->name(), "graphics-service") == 0) {
                        graphicsService_->load(child);
                    }
                }
            }
        }

        void saveConfig(rapidxml::xml_node<> *parent)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "game");
            if (propertyService_.get()) {
                propertyService_->save(node);
            }
            if (controlService_.get()) {
                controlService_->save(node);
            }
            if (physicsService_.get()) {
                physicsService_->save(node);
            }
            if (graphicsService_.get()) {
                graphicsService_->save(node);
            }
        }

        void loadModule(char const *file)
        {
            std::auto_ptr<Stream> stream = createStreamFromFile(file, "rb");
            
            int size = stream->seek(0, RW_SEEK_END);
            stream->seek(0, RW_SEEK_SET);
            std::vector<char> buffer(size + 1);
            stream->read(&buffer[0], size);
            buffer.back() = 0;
            
            rapidxml::xml_document<> document;
            document.parse<0>(&buffer[0]);
            for (rapidxml::xml_node<> *child = document.first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element &&
                    strcmp(child->name(), "module") == 0)
                {
                    loadGroup(child);
                }
            }
        }

        void saveModule(char const *file)
        {
            rapidxml::xml_document<> document;
            rapidxml::xml_node<> *node = saveGroup(&document, "module");
            for (std::size_t i = 0; i < actors_.size(); ++i) {
                actors_[i]->save(node);
            }
            std::ofstream out(file);
            out << document;
        }

        float getTime() const
        {
            return time_;
        }

        PropertyService *getPropertyService()
        {
            return propertyService_.get();
        }

        PropertyService const *getPropertyService() const
        {
            return propertyService_.get();
        }        

        ControlService *getControlService()
        {
            return controlService_.get();
        }
        
        ControlService const *getControlService() const
        {
            return controlService_.get();
        }

        PhysicsService *getPhysicsService()
        {
            return physicsService_.get();
        }
        
        PhysicsService const *getPhysicsService() const
        {
            return physicsService_.get();
        }

        GraphicsService *getGraphicsService()
        {
            return graphicsService_.get();
        }
        
        GraphicsService const *getGraphicsService() const
        {
            return graphicsService_.get();
        }

        void update(float dt)
        {
            time_ += dt;
            controlService_->update(dt);
            physicsService_->update(dt);
            graphicsService_->update(dt);
        }

        Actor *findActor(char const *name)
        {
            for (std::size_t i = 0; i < actors_.size(); ++i) {
                char const *actorName = actors_[i]->getName();
                if (actorName && std::strcmp(actorName, name) == 0) {
                    return actors_[i];
                }
            }
            return 0;
        }

        Actor const *findActor(char const *name) const
        {
            return const_cast<DefaultGame *>(this)->findActor(name);
        }

    private:
        float time_;
        std::auto_ptr<PropertyService> propertyService_;
        std::auto_ptr<ControlService> controlService_;
        std::auto_ptr<PhysicsService> physicsService_;
        std::auto_ptr<GraphicsService> graphicsService_;
        std::vector<Actor *> actors_;

        void loadGroup(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (strcmp(child->name(), "group") == 0) {
                        loadGroup(child);
                    }
                    if (strcmp(child->name(), "module-ref") == 0) {
                        std::string file;
                        file += "../../../content/modules/";
                        file += child->value();
                        file += ".xml";
                        loadModule(file.c_str());
                    }
                    if (strcmp(child->name(), "actor") == 0) {
                        std::auto_ptr<Actor> actor = createActor(this);
                        actor->load(child);
                        actors_.push_back(actor.release());
                    }
                }
            }
        }
    };

    std::auto_ptr<Game> createGame(boost::intrusive_ptr<Context> context)
    {
        return std::auto_ptr<Game>(new DefaultGame(context));
    }
}
