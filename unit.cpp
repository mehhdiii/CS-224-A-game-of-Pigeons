#include "unit.hpp"


void Unit::draw(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, assets, &src, &mover);
}

Unit::Unit(SDL_Texture* tex): assets(tex){}

SDL_Rect Unit::getMover(){return mover;}