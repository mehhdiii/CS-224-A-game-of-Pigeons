#include"nest.hpp"

Nest::Nest(SDL_Texture * texture):Unit(texture){

    src = {170,192,440,406}; 
}


void Nest::draw(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, assets, &src, &mover);
}

Nest::~Nest(){
    
}
