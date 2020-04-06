
#include "unit.hpp"
// #include"pigoen.hpp"
#pragma once


class Egg: public Unit{
    SDL_Rect src;
public:
    Egg(SDL_Texture* tex);
    // Egg(SDL_Texture*, SDL_Rect);
    void draw(SDL_Renderer*);
    // bool dropped();
    // bool operator>=(Pigeon*);
    // bool operator<=(Pigeon*);
    // bool operator==(Pigoen*);
};