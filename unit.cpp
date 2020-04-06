#include"unit.hpp"
#include<iostream>
using namespace std;

Unit::Unit (SDL_Texture* input_texture): assets(input_texture){
    
}
SDL_Rect Unit::getMover(){
    return mover;
}

// bool Unit::operator>=(Unit *myobj){
//     return mover.x >= myobj->mover.x && mover.y >= myobj->mover.y ;
// }

// bool Unit::operator<=(Unit *myobj){
//     return mover.x <= myobj->mover.x && mover.y <= myobj->mover.y;
// }

// bool Unit::operator==(Unit *myobj){
//     return mover.x <= myobj->mover.x && mover.y <= myobj->mover.y;
// }
// Unit* Unit::operator+(int r){
//     mover.x+r;
//     mover.y+r;
//     return this;
// }
// void Unit::draw(SDL_Renderer* renderer){

//     // SDL_RenderClear( renderer );
//     SDL_RenderCopy(renderer, assets, NULL, NULL);
//     // SDL_RenderPresent( renderer );
    
// }

void Unit::setCoordinates(int x, int y){
    mover.x = x;
    mover.y = y;
}
Unit::~Unit(){
    // assets = {0, 0, 0, 0};
    delete this;
}
