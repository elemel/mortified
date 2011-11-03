#include "default_game.hpp"

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
        DefaultGame() :
            time_(0.0f),
            propertyService_(createPropertyService()),
            controlService_(createControlService()),
            physicsService_(createPhysicsService()),
            graphicsService_(createGraphicsService())
        { }

        void load(char const *file)
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

        void save(char const *file)
        {
            rapidxml::xml_document<> document;
            rapidxml::xml_node<> *node = saveGroup(&document, "group");
            for (ActorIterator i = actors_.begin(); i != actors_.end(); ++i)
            {
                (*i)->save(node);
            }
            std::ofstream out(file);
            out << document;
        }

        float time() const
        {
            return time_;
        }

        PropertyService *propertyService()
        {
            return propertyService_.get();
        }

        PropertyService const *propertyService() const
        {
            return propertyService_.get();
        }        

        ControlService *controlService()
        {
            return controlService_.get();
        }
        
        ControlService const *controlService() const
        {
            return controlService_.get();
        }

        PhysicsService *physicsService()
        {
            return physicsService_.get();
        }
        
        PhysicsService const *physicsService() const
        {
            return physicsService_.get();
        }

        GraphicsService *graphicsService()
        {
            return graphicsService_.get();
        }
        
        GraphicsService const *graphicsService() const
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

        ActorRange actors()
        {
            return ActorRange(actors_.begin(), actors_.end());
        }

        ConstActorRange actors() const
        {
            return ConstActorRange(actors_.begin(), actors_.end());
        }
        
        ActorIterator addActor(ActorPtr actor)
        {
            return actors_.insert(actors_.end(), actor);
        }

        void removeActor(ActorIterator actor)
        {
            actors_.erase(actor);
        }

        ActorPtr findActor(char const *name)
        {
            for (ActorIterator i = actors_.begin(); i != actors_.end(); ++i) {
                char const *actorName = (*i)->name();
                if (actorName && std::strcmp(actorName, name) == 0) {
                    return *i;
                }
            }
            return ActorPtr();
        }

    private:
        float time_;
        std::auto_ptr<PropertyService> propertyService_;
        std::auto_ptr<ControlService> controlService_;
        std::auto_ptr<PhysicsService> physicsService_;
        std::auto_ptr<GraphicsService> graphicsService_;
        ActorList actors_;

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
                        load(file.c_str());
                    }
                    if (strcmp(child->name(), "actor") == 0) {
                        ActorPtr actor = createActor(this);
                        actor->load(child);
                        addActor(actor);
                    }
                }
            }
        }
    };

    std::auto_ptr<Game> createGame()
    {
        return std::auto_ptr<Game>(new DefaultGame);
    }
}
