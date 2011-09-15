#ifndef MORTIFIED_DEFAULT_CAMERA_HPP
#define MORTIFIED_DEFAULT_CAMERA_HPP

#include <memory>

namespace mortified {
    class Camera;

    std::auto_ptr<Camera> createCamera();
}

#endif
