#include "default_physics_component.hpp"

#include "game.hpp"
#include "game_object.hpp"
#include "physics_component.hpp"

#include <cstdlib>

namespace mortified {
    class DefaultPhysicsComponent : public virtual PhysicsComponent {
    public:
        explicit DefaultPhysicsComponent(GameObject *object) :
            gameObject_(object)
        { }

        const char *type() const
        {
            return "physics";
        }

        void load(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "body") == 0) {
                        loadBody(child);
                    }
                }
            }
        }

        void save(rapidxml::xml_node<> *node)
        { }
        
        void update(float dt)
        { }

    private:
        GameObject *gameObject_;
        BodyList bodies_;

        void loadBody(rapidxml::xml_node<> *node)
        {
            b2BodyDef def;
            loadBodyData(&def, node);
            b2Body *body = gameObject_->game()->world()->CreateBody(&def);
            bodies_.push_back(body);
            loadFixtures(body, node);
        }

        void loadBodyData(b2BodyDef *def, rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "position") == 0) {
                        def->position = loadVec2(child);
                    }
                    if (std::strcmp(child->name(), "angle") == 0) {
                        def->angle = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "linear-velocity") == 0) {
                        def->linearVelocity = loadVec2(child);
                    }
                    if (std::strcmp(child->name(), "angular-velocity") == 0) {
                        def->angularVelocity = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "linear-damping") == 0) {
                        def->linearDamping = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "angular-damping") == 0) {
                        def->angularDamping = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "allow-sleep") == 0) {
                        def->allowSleep = loadBool(child);
                    }
                    if (std::strcmp(child->name(), "awake") == 0) {
                        def->awake = loadBool(child);
                    }
                    if (std::strcmp(child->name(), "fixed-rotation") == 0) {
                        def->fixedRotation = loadBool(child);
                    }
                    if (std::strcmp(child->name(), "bullet") == 0) {
                        def->bullet = loadBool(child);
                    }
                    if (std::strcmp(child->name(), "type") == 0) {
                        def->type = loadBodyType(child);
                    }
                    if (std::strcmp(child->name(), "active") == 0) {
                        def->active = loadBool(child);
                    }
                    if (std::strcmp(child->name(), "gravity-scale") == 0) {
                        def->gravityScale = loadFloat(child);
                    }
                }
            }
        }
        
        b2BodyType loadBodyType(rapidxml::xml_node<> *node)
        {
            if (std::strcmp(node->value(), "static") == 0) {
                return b2_staticBody;
            }
            if (std::strcmp(node->value(), "kinematic") == 0) {
                return b2_kinematicBody;
            }
            if (std::strcmp(node->value(), "dynamic") == 0) {
                return b2_dynamicBody;
            }
            return b2_staticBody;
        }

        void loadFixtures(b2Body *body, rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "fixture") == 0) {
                        loadFixture(body, child);
                    }
                }
            }
        }
        
        void loadFixture(b2Body *body, rapidxml::xml_node<> *node)
        {
            b2FixtureDef def;
            loadFixtureData(&def, node);
            loadFixtureShape(body, &def, node);
        }

        void loadFixtureData(b2FixtureDef *def, rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "friction") == 0) {
                        def->friction = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "restitution") == 0) {
                        def->restitution = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "density") == 0) {
                        def->density = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "sensor") == 0) {
                        def->isSensor = loadBool(child);
                    }
                }
            }
        }
        
        void loadFixtureShape(b2Body *body, b2FixtureDef *def,
                              rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "circle") == 0) {
                        loadCircleFixture(body, def, child);
                    }
                    if (std::strcmp(child->name(), "polygon") == 0) {
                        loadPolygonFixture(body, def, child);
                    }
                }
            }
        }

        void loadCircleFixture(b2Body *body, b2FixtureDef *def,
                               rapidxml::xml_node<> *node)
        {
            b2CircleShape shape;
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "center") == 0) {
                        shape.m_p = loadVec2(child);
                    }
                    if (std::strcmp(child->name(), "radius") == 0) {
                        shape.m_radius = loadFloat(child);
                    }
                }
            }
            def->shape = &shape;
            body->CreateFixture(def);
        }

        void loadPolygonFixture(b2Body *body, b2FixtureDef *def,
                                rapidxml::xml_node<> *node)
        {
            b2Vec2 vertices[b2_maxPolygonVertices];
            int vertexCount = 0;
            for (rapidxml::xml_node<> *child = node->first_node();
                 child && vertexCount < b2_maxPolygonVertices;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "vertex") == 0) {
                        vertices[vertexCount++] = loadVec2(child);
                    }
                }
            }

            b2PolygonShape shape;
            shape.Set(vertices, vertexCount);
            def->shape = &shape;
            body->CreateFixture(def);
        }

        bool loadBool(rapidxml::xml_node<> *node)
        {
            if (std::strcmp(node->value(), "false") == 0) {
                return false;
            }
            if (std::strcmp(node->value(), "true") == 0) {
                return true;
            }
            return false;
        }

        float loadFloat(rapidxml::xml_node<> *node)
        {
            return float(std::atof(node->value()));
        }

        b2Vec2 loadVec2(rapidxml::xml_node<> *node)
        {
            b2Vec2 v;
            v.SetZero();
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "x") == 0) {
                        v.x = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "y") == 0) {
                        v.y = loadFloat(child);
                    }
                }
            }
            return v;
        }
    };

    boost::shared_ptr<PhysicsComponent>
    createPhysicsComponent(GameObject *object)
    {
        return boost::shared_ptr<PhysicsComponent>(new DefaultPhysicsComponent(object));
    }
}
