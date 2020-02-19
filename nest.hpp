#include "unit.hpp"
#pragma once
class Nest: public Unit{
public:
    Nest(SDL_Texture* tex);
    Nest(SDL_Texture* tex, SDL_Rect);
};