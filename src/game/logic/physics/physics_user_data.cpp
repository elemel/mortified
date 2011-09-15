#include "physics_user_data.hpp"

namespace mortified {
    Actor *getUserData(b2Fixture *fixture)
    {
        assert(fixture);
        return reinterpret_cast<Actor *>(fixture->GetUserData());
    }

    void setUserData(b2Fixture *fixture, Actor *actor)
    {
        assert(fixture);
        fixture->SetUserData(reinterpret_cast<void *>(actor));
    }
}
