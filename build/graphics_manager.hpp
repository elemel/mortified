#ifndef MORTIFIED_GRAPHICS_MANAGER_HPP
#define MORTIFIED_GRAPHICS_MANAGER_HPP

#include <list>
#include <utility>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class GraphicsResource;
    
    class GraphicsManager {
    public:
        typedef boost::shared_ptr<GraphicsResource> ResourcePtr;
        typedef std::list<ResourcePtr> ResourceList;
        typedef ResourceList::iterator ResourceIterator;
        typedef ResourceList::const_iterator ConstResourceIterator;
        typedef std::pair<ResourceIterator, ResourceIterator> ResourceRange;
        typedef std::pair<ConstResourceIterator, ConstResourceIterator>
            ConstResourceRange;

        virtual ~GraphicsManager()
        { }

        virtual ResourceRange resources() = 0;
        virtual ConstResourceRange resources() const = 0;

        virtual ResourceIterator addResource(ResourcePtr resource) = 0;
        virtual ResourcePtr removeResource(ResourceIterator resource) = 0;

        virtual void create() = 0;
        virtual void destroy() = 0;
        virtual void invalidate() = 0;
    };
}

#endif
