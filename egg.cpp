#include"egg.hpp"


Egg::Egg (SDL_Texture * tex): Unit(tex){
    src = {226, 12, 360, 190};
    mover = {0, 0, 25, 25};
}

void Egg::draw(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, assets, &src, &mover);
    mover.y+=15;
}