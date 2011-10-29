#include "default_game.hpp"

#include "default_game_object.hpp"
#include "default_graphics_service.hpp"
#include "default_physics_service.hpp"
#include "default_stream.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "graphics_service.hpp"
#include "physics_service.hpp"
#include "stream.hpp"
#include "xml.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>

namespace mortified {
    class DefaultGame : public virtual Game {
    public:
        DefaultGame() :
            time_(0.0f),
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
            for (ObjectIterator i = objects_.begin(); i != objects_.end(); ++i)
            {
                (*i)->save(node);
            }
        }

        float time() const
        {
            return time_;
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
            physicsService_->update(dt);
            graphicsService_->update(dt);
        }

        ObjectRange objects()
        {
            return ObjectRange(objects_.begin(), objects_.end());
        }

        ConstObjectRange objects() const
        {
            return ConstObjectRange(objects_.begin(), objects_.end());
        }
        
        ObjectIterator addObject(ObjectPtr object)
        {
            return objects_.insert(objects_.end(), object);
        }

        void removeObject(ObjectIterator object)
        {
            objects_.erase(object);
        }

    private:
        float time_;
        std::auto_ptr<PhysicsService> physicsService_;
        std::auto_ptr<GraphicsService> graphicsService_;
        ObjectList objects_;

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
                    if (strcmp(child->name(), "object") == 0) {
                        boost::shared_ptr<GameObject> object =
                        createGameObject(this);
                        object->load(child);
                        addObject(object);
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
