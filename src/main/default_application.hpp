#ifndef MORTIFIED_DEFAULT_APPLICATION_HPP
#define MORTIFIED_DEFAULT_APPLICATION_HPP

#include <memory>

namespace mortified {
    class Application;

    std::auto_ptr<Application> createApplication();
}

#endif
