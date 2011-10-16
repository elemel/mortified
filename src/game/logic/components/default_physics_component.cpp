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
        
        ~DefaultPhysicsComponent()
        {
            while (!joints_.empty()) {
                gameObject_->game()->world()->DestroyJoint(joints_.back().joint);
                joints_.pop_back();
            }
            while (!bodies_.empty()) {
                gameObject_->game()->world()->DestroyBody(bodies_.back().body);
                bodies_.pop_back();
            }
        }

        const char *type() const
        {
            return "physics";
        }

        void load(rapidxml::xml_node<> *node)
        {
            loadBodies(node);
            loadJoints(node);
        }

        void save(rapidxml::xml_node<> *parent)
        {
            saveBodies(parent);
        }
        
        void update(float dt)
        { }

    private:
        GameObject *gameObject_;
        BodyList bodies_;
        JointList joints_;

        b2Body *findBody(char const *name)
        {
            for (BodyIterator i = bodies_.begin(); i != bodies_.end(); ++i) {
                if (i->name == name) {
                    return i->body;
                }
            }
            return 0;
        }

        void loadBodies(rapidxml::xml_node<> *node)
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

        void loadBody(rapidxml::xml_node<> *node)
        {
            std::string name;
            b2BodyDef def;
            loadBodyData(&name, &def, node);
            b2Body *body = gameObject_->game()->world()->CreateBody(&def);
            bodies_.push_back(BodyData(this, body, name));
            loadFixtures(body, node);
        }

        void loadBodyData(std::string *name, b2BodyDef *def,
                          rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "name") == 0) {
                        *name = child->value();
                    }
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
                    if (std::strcmp(child->name(), "sleeping-allowed") == 0) {
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

        void loadJoints(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "revolute-joint") == 0) {
                        loadRevoluteJoint(child);
                    }
                }
            }
        }

        void loadRevoluteJoint(rapidxml::xml_node<> *node)
        {
            b2Body *bodyA = 0;
            b2Body *bodyB = 0;
            b2Vec2 anchor(0.0f, 0.0f);
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "body-a") == 0) {
                        bodyA = findBody(child->value());
                    }
                    if (std::strcmp(child->name(), "body-b") == 0) {
                        bodyB = findBody(child->value());
                    }
                    if (std::strcmp(child->name(), "anchor") == 0) {
                        anchor = loadVec2(child);
                    }
                }
            }

            if (bodyA && bodyB) {
                std::string name;
                b2RevoluteJointDef def;
                def.Initialize(bodyA, bodyB, anchor);
                for (rapidxml::xml_node<> *child = node->first_node();
                     child; child = child->next_sibling())
                {
                    if (child->type() == rapidxml::node_element) {
                        if (std::strcmp(child->name(), "collide-connected") == 0) {
                            def.collideConnected = loadBool(child);
                        }
                        if (std::strcmp(child->name(), "limit-enabled") == 0) {
                            def.enableLimit = loadBool(child);
                        }
                        if (std::strcmp(child->name(), "lower-limit") == 0) {
                            def.lowerAngle = loadFloat(child);
                        }
                        if (std::strcmp(child->name(), "upper-limit") == 0) {
                            def.upperAngle = loadFloat(child);
                        }
                        if (std::strcmp(child->name(), "motor-enabled") == 0) {
                            def.enableMotor = loadBool(child);
                        }
                        if (std::strcmp(child->name(), "motor-speed") == 0) {
                            def.motorSpeed = loadFloat(child);
                        }
                        if (std::strcmp(child->name(), "max-motor-torque") == 0) {
                            def.maxMotorTorque = loadFloat(child);
                        }
                    }
                }
                b2Joint *joint = gameObject_->game()->world()->CreateJoint(&def);
                joints_.push_back(JointData(this, joint, name));
            }
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
            b2Vec2 vec;
            vec.SetZero();
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "x") == 0) {
                        vec.x = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "y") == 0) {
                        vec.y = loadFloat(child);
                    }
                }
            }
            return vec;
        }

        void saveBodies(rapidxml::xml_node<> *parent)
        {
            for (BodyIterator i = bodies_.begin(); i != bodies_.end(); ++i) {
                saveBody(parent, i->name.c_str(), i->body);
            }
        }

        void saveBody(rapidxml::xml_node<> *parent, char const *name,
                      b2Body *body)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "body");
            saveString(node, "name", name);
            saveVec2(node, "position", body->GetPosition());
            saveFloat(node, "angle", body->GetAngle());
            saveVec2(node, "linear-velocity", body->GetLinearVelocity());
            saveFloat(node, "angular-velocity", body->GetAngularVelocity());
            saveFloat(node, "linear-damping", body->GetLinearDamping());
            saveFloat(node, "angular-damping", body->GetAngularDamping());
            saveBool(node, "sleeping-allowed", body->IsSleepingAllowed());
            saveBool(node, "awake", body->IsAwake());
            saveBool(node, "fixed-rotation", body->IsFixedRotation());
            saveBool(node, "bullet", body->IsBullet());
            saveBodyType(node, "type", body->GetType());
            saveBool(node, "active", body->IsActive());
            saveFloat(node, "gravity-scale", body->GetGravityScale());
        }

        rapidxml::xml_node<> *
        saveGroup(rapidxml::xml_node<> *parent, char const *name)
        {
            rapidxml::xml_document<> *document = parent->document();
            rapidxml::xml_node<> *node =
                document->allocate_node(rapidxml::node_element,
                                        document->allocate_string(name));
            parent->append_node(node);
            return node;
        }

        void saveString(rapidxml::xml_node<> *parent, char const *name,
                        char const *value)
        {
            rapidxml::xml_document<> *document = parent->document();
            rapidxml::xml_node<> *node =
                document->allocate_node(rapidxml::node_element,
                                        document->allocate_string(name),
                                        document->allocate_string(value));
            parent->append_node(node);
        }

        void saveBool(rapidxml::xml_node<> *parent, char const *name, bool b)
        {
            saveString(parent, name, b ? "true" : "false");
        }

        void saveFloat(rapidxml::xml_node<> *parent, char const *name, float f)
        {
            char buffer[32];
            sprintf(buffer, "%g", f);
            saveString(parent, name, buffer);
        }

        void saveVec2(rapidxml::xml_node<> *parent, char const *name,
                      b2Vec2 vec)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, name);
            saveFloat(node, "x", vec.x);
            saveFloat(node, "y", vec.y);
        }

        void saveBodyType(rapidxml::xml_node<> *parent, char const *name,
                          b2BodyType type)
        {
            switch (type) {
            case b2_staticBody:
                saveString(parent, name, "static");
                break;

            case b2_kinematicBody:
                saveString(parent, name, "kinematic");
                break;

            case b2_dynamicBody:
                saveString(parent, name, "dynamic");
                break;
            }
        }
    };

    boost::shared_ptr<PhysicsComponent>
    createPhysicsComponent(GameObject *object)
    {
        return boost::shared_ptr<PhysicsComponent>(new DefaultPhysicsComponent(object));
    }
}
