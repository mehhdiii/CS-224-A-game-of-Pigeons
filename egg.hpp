#include "unit.hpp"
#pragma once

class Egg: public Unit{
public:
    Egg(SDL_Texture* tex);
    Egg(SDL_Texture*, SDL_Rect);
    void draw(SDL_Renderer*);
    bool dropped();
};