#ifndef MORTIFIED_DEFAULT_CONTROL_SERVICE_HPP
#define MORTIFIED_DEFAULT_CONTROL_SERVICE_HPP

#include <memory>

namespace mortified {
    class ControlService;
    
    std::auto_ptr<ControlService> createControlService();
}

#endif
