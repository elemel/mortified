#ifndef MORTIFIED_SCENE_CHARACTER_HPP
#define MORTIFIED_SCENE_CHARACTER_HPP

#include <boost/shared_ptr.hpp>

namespace mortified {
    class CharacterActor;
    class Scene;
    class SceneObject;

    boost::shared_ptr<SceneObject>
    createSceneCharacter(Scene *scene, CharacterActor *actor);
}

#endif
