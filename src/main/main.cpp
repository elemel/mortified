#include "application.hpp"
#include "default_application.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
#ifndef NDEBUG
    return mortified::createApplication()->main(argc, argv);
#else
    try {
        return mortified::createApplication()->main(argc, argv);
    } catch (std::exception const &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return 1;
    }
#endif
}
