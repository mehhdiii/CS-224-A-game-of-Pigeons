#include"egg.hpp"


Egg::Egg (SDL_Texture * tex): Unit(tex){
    src = {226, 12, 360, 190};
}

void Egg::draw(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, assets, &src, &mover);
}