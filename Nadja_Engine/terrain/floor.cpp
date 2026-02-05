#include "floor.hpp"

Floor::Floor(SDL_Texture* texture)
    : Actor(texture, 64, 64) // tamanho do chão
{
    name = "Floor";
    this->texture = texture;

    bodyType = BodyType::STATIC; //CHÃO NÃO SE MOVE
}

void Floor::start() {
    bodyType = BodyType::STATIC;
}
