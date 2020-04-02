#include "SDL.h"
#pragma once
class Unit{
public:
    SDL_Texture* assets;
    SDL_Rect src;
    SDL_Rect mover = {0,0,50,50};
public:
    Unit(SDL_Texture*);
    virtual void draw(SDL_Renderer*);
    SDL_Rect getMover(int,int);
    virtual ~Unit();
};