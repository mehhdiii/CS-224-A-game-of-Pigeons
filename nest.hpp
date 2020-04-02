#include "unit.hpp"
#pragma once
class Nest: public Unit{
    SDL_Rect src; 
    
public:
    Nest(SDL_Texture* tex);
    Nest(SDL_Texture*, SDL_Rect);
    void draw(SDL_Renderer*);
    ~Nest();
};