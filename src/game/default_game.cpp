#include "default_game.hpp"

#include "context.hpp"
#include "control_service.hpp"
#include "default_control_service.hpp"
#include "default_actor.hpp"
#include "default_physics_service.hpp"
#include "default_property_service.hpp"
#include "default_render_service.hpp"
#include "default_stream.hpp"
#include "game.hpp"
#include "actor.hpp"
#include "physics_service.hpp"
#include "property_service.hpp"
#include "render_service.hpp"
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
            renderService_(createRenderService(context))
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
            for (rapidxml::xml_node<> *childNode = node->first_node();
                 childNode; childNode = childNode->next_sibling())
            {
                if (childNode->type() == rapidxml::node_element) {
                    if (strcmp(childNode->name(), "property-service") == 0) {
                        propertyService_->load(childNode);
                    }
                    if (strcmp(childNode->name(), "control-service") == 0) {
                        controlService_->load(childNode);
                    }
                    if (strcmp(childNode->name(), "physics-service") == 0) {
                        physicsService_->load(childNode);
                    }
                    if (strcmp(childNode->name(), "render-service") == 0) {
                        renderService_->load(childNode);
                    }
                }
            }
        }

        void saveConfig(rapidxml::xml_node<> *parentNode)
        {
            rapidxml::xml_node<> *node = saveGroup(parentNode, "game");
            if (propertyService_.get()) {
                propertyService_->save(node);
            }
            if (controlService_.get()) {
                controlService_->save(node);
            }
            if (physicsService_.get()) {
                physicsService_->save(node);
            }
            if (renderService_.get()) {
                renderService_->save(node);
            }
        }

        void loadModule(char const *file, Matrix3 parentTransform)
        {
            std::auto_ptr<Stream> stream = createStreamFromFile(file, "rb");
            
            int size = stream->seek(0, RW_SEEK_END);
            stream->seek(0, RW_SEEK_SET);
            std::vector<char> buffer(size + 1);
            stream->read(&buffer[0], size);
            buffer.back() = 0;
            
            rapidxml::xml_document<> document;
            document.parse<0>(&buffer[0]);
            for (rapidxml::xml_node<> *childNode = document.first_node();
                 childNode; childNode = childNode->next_sibling())
            {
                if (childNode->type() == rapidxml::node_element &&
                    strcmp(childNode->name(), "module") == 0)
                {
                    loadGroup(childNode, parentTransform);
                }
            }
        }

        void saveModule(char const *file, Matrix3 parentTransform)
        {
            rapidxml::xml_document<> document;
            rapidxml::xml_node<> *node = saveGroup(&document, "module");
            for (std::size_t i = 0; i < actors_.size(); ++i) {
                actors_[i]->save(node, parentTransform);
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

        RenderService *getRenderService()
        {
            return renderService_.get();
        }
        
        RenderService const *getRenderService() const
        {
            return renderService_.get();
        }

        void update(float dt)
        {
            time_ += dt;
            controlService_->update(dt);
            physicsService_->update(dt);
            renderService_->update(dt);
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
        std::auto_ptr<RenderService> renderService_;
        std::vector<Actor *> actors_;

        void loadGroup(rapidxml::xml_node<> *node, Matrix3 parentTransform)
        {
            Matrix3 localTransform = loadTransform(node);
            Matrix3 transform = parentTransform * localTransform;
            for (rapidxml::xml_node<> *childNode = node->first_node();
                 childNode; childNode = childNode->next_sibling())
            {
                if (childNode->type() == rapidxml::node_element) {
                    if (strcmp(childNode->name(), "group") == 0) {
                        loadGroup(childNode, transform);
                    }
                    if (strcmp(childNode->name(), "module-ref") == 0) {
                        std::string file;
                        file += "../../../data/modules/";
                        file += childNode->value();
                        file += ".xml";
                        loadModule(file.c_str(), transform);
                    }
                    if (strcmp(childNode->name(), "actor") == 0) {
                        std::auto_ptr<Actor> actor = createActor(this);
                        actor->load(childNode, transform);
                        actors_.push_back(actor.release());
                    }
                }
            }
        }

        Matrix3 loadTransform(rapidxml::xml_node<> *node)
        {
            Vector2 position;
            float angle = 0.0f;
            for (rapidxml::xml_node<> *childNode = node->first_node();
                 childNode; childNode = childNode->next_sibling())
            {
                if (childNode->type() == rapidxml::node_element) {
                    if (strcmp(childNode->name(), "position") == 0) {
                        position = loadVector2(childNode);
                    }
                    if (strcmp(childNode->name(), "angle") == 0) {
                        angle = loadFloat(childNode);
                    }
                }
            }

            Matrix3 transform;
            transform.translate(position);
            transform.rotate(angle);
            return transform;
        }
    };

    std::auto_ptr<Game> createGame(boost::intrusive_ptr<Context> context)
    {
        return std::auto_ptr<Game>(new DefaultGame(context));
    }
}
