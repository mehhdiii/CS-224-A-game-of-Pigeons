#include"unit.hpp"
#include<iostream>
using namespace std;

Unit::Unit (SDL_Texture* input_texture): assets(input_texture){
    // cout << "a unit created" <<endl;
}

void Unit::draw(SDL_Renderer* renderer){

    // SDL_RenderClear( renderer );
    SDL_RenderCopy(renderer, assets, NULL, NULL);
    // SDL_RenderPresent( renderer );
    
}
Unit::~Unit(){}
// SDL_Rect Unit::setMover(){
    
// }