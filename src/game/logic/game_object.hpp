#ifndef MORTIFIED_GAME_OBJECT_HPP
#define MORTIFIED_GAME_OBJECT_HPP

#include <list>
#include <utility>
#include <rapidxml.hpp>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class Component;
    class Game;
    
    class GameObject {
    public:
        typedef boost::shared_ptr<Component> ComponentPtr;
        typedef std::list<ComponentPtr> ComponentList;
        typedef ComponentList::iterator ComponentIterator;
        typedef ComponentList::const_iterator ConstComponentIterator;
        typedef std::pair<ComponentIterator, ComponentIterator> ComponentRange;
        typedef std::pair<ConstComponentIterator, ConstComponentIterator>
            ConstComponentRange;

        virtual ~GameObject()
        { }
        
        virtual Game *game() = 0;
        virtual Game const *game() const = 0;

        virtual void load(rapidxml::xml_node<> *node) = 0;
        virtual void save(rapidxml::xml_node<> *node) = 0;

        virtual ComponentRange components() = 0;
        virtual ConstComponentRange components() const = 0;
        
        virtual ComponentIterator addComponent(ComponentPtr component) = 0;
        virtual void removeComponent(ComponentIterator component) = 0;

        virtual void update(float dt) = 0;
    };
}

#endif
