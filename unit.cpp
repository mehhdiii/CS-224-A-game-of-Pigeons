#include"unit.hpp"
#include<iostream>
using namespace std;

Unit::Unit (SDL_Texture* input_texture): assets(input_texture){
    // cout << "a unit created" <<endl;
}
SDL_Rect Unit::getMover(){
    return mover;
}

// void Unit::draw(SDL_Renderer* renderer){

//     // SDL_RenderClear( renderer );
//     SDL_RenderCopy(renderer, assets, NULL, NULL);
//     // SDL_RenderPresent( renderer );
    
// }

void Unit::setCoordinates(int x, int y){
    mover.x = x;
    mover.y = y;
}
Unit::~Unit(){}
// SDL_Rect Unit::setMover(){
    
// }