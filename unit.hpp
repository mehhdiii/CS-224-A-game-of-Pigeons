#include "SDL.h"
#pragma once
class Unit{
protected:
    SDL_Texture* assets;
    SDL_Rect src;
    SDL_Rect mover;
public:
    Unit(SDL_Texture*);
    void draw(SDL_Renderer*);
    SDL_Rect getMover();
};