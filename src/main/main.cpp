#include "application.hpp"
#include "default_application.hpp"

#include <memory>

int main(int argc, char **argv)
{
    return mortified::createApplication()->main(argc, argv);
}
