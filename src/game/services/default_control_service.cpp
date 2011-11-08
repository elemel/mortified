#include "default_control_service.hpp"

#include "control_service.hpp"

#include <stdexcept>

namespace mortified {
    class DefaultControlService : public virtual ControlService {
    public:
        void load(rapidxml::xml_node<> *node)
        { }

        void save(rapidxml::xml_node<> *parent)
        { }

        void update(float dt)
        {
            for (UpdateHandlerIterator i = handlers_.begin();
                 i != handlers_.end(); ++i)
            {
                (*i)(dt);
            }
        }

        UpdateHandlerIterator addUpdateHandler(UpdateHandler handler)
        {
            return handlers_.insert(handlers_.end(), handler);
        }
        
        void removeUpdateHandler(UpdateHandlerIterator handler)
        {
            handlers_.erase(handler);
        }

    private:
        UpdateHandlerList handlers_;
    };
    
    std::auto_ptr<ControlService> createControlService()
    {
        return std::auto_ptr<ControlService>(new DefaultControlService);
    }
}
