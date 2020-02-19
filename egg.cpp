
#include "egg.hpp"
Egg::Egg(SDL_Texture* tex): Unit(tex){
    src={228, 14, 132, 174};
    mover = {rand()%800, 200, 20, 30};
}

Egg::Egg(SDL_Texture* tex, SDL_Rect rect): Egg(tex){
    mover.x = rect.x+20;
    mover.y = rect.y+40;
}

void Egg::draw(SDL_Renderer* renderer){
    Unit::draw(renderer);   
    mover.y+=5;  
}

bool Egg::dropped(){
    return mover.y >= 550;
}
