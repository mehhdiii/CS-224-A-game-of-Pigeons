#include "pigeon.hpp"


void Pigeon::draw(SDL_Renderer *renderer){
    Unit::src = src[frame];
    Unit::draw(renderer);    
    frame++;
    if (frame==3) frame = 0;
    if (baby){
        mover.w++;
        mover.h++;
    } 
    if(mover.w>=50) baby = false;
    
    if(mover.y>20){
        if(mover.x < 700) mover.x+=rand()%10;
        mover.y-=rand()%10;
    }
}

Pigeon::Pigeon(SDL_Texture* tex):Unit(tex){
    src[0] = {0,0,160,133};
    src[1] = {0,133,160,133};
    src[2] = {0,266,160,133};

    mover.x = rand() % 800;
    mover.y = 50;
    mover.h  = mover.w = 50;
    eggsLaid = 0;
    frame = 0;
    baby = false;    
}

Pigeon::Pigeon(SDL_Texture* tex, SDL_Rect rect): Pigeon(tex){
    mover.x = rect.x;
    mover.y = rect.y;
}
Pigeon::Pigeon(SDL_Texture* tex, SDL_Rect rect, bool bab): Pigeon(tex, rect){
    baby = bab;
    mover.h = mover.w = 5;
}

bool Pigeon::layEgg(){
    if (baby) return false;
    eggsLaid++;
    return true;
}

bool Pigeon::isAlive(){
    return eggsLaid >= 4;
}