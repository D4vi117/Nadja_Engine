#include "sprite.hpp"

class Actor : public Sprite {
public:
    Actor(SDL_Texture* texture, float w, float h);
    virtual void serializeState(nlohmann::json& out) const {}
    virtual void deserializeState(const nlohmann::json& in) {}

};
