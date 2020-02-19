#include "nest.hpp"
#include "SDL.h"
Nest::Nest(SDL_Texture* tex): Unit(tex) {
    src = {176,200,269,206};
    mover = {rand()%700, 500, 50, 50};
}

Nest::Nest(SDL_Texture* tex, SDL_Rect rect): Nest(tex){
    mover.x = rect.x;
    mover.y = rect.y;
}