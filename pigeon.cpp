#include "pigeon.hpp"

void Pigeon::fly(){
    if (mover.x<500) mover.x++;
    draw();
    if(frame>2) frame = 0;
}

void Pigeon::draw(){
    SDL_RenderCopy(renderer, assets, &src[frame++], &mover);

}

Pigeon::Pigeon(SDL_Renderer* rend, SDL_Texture* tex){
    src[0] = {0,0,160,133};
    src[1] = {0,133,160,133};
    src[2] = {0,266,160,133};
    assets = tex;
    renderer = rend;
}

Pigeon::Pigeon(){
    src[0] = {0,0,160,133};
    src[1] = {0,133,160,133};
    src[2] = {0,266,160,133};
    assets = NULL;
    renderer = NULL;  
}