#include "pigeon.hpp"

void Pigeon::draw(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, assets, &src, &mover);

}

Pigeon::Pigeon(SDL_Texture* tex){
    src = {0,0,160,133};
    assets = tex;
}

Pigeon::Pigeon(){
    src = {0,0,160,133};
    assets = NULL;
}