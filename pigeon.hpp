#pragma once
#include "unit.hpp"
class Pigeon: public Unit{
    int eggsLaid; //no. of eggs laid
    bool baby;      // is it a baby pigeon?
    SDL_Rect src[3]; // three textures, to make the fly animation
    int frame;    
public:
    Pigeon(SDL_Texture*);
    Pigeon(SDL_Texture*, SDL_Rect);
    Pigeon(SDL_Texture*, SDL_Rect, bool);
    void draw(SDL_Renderer*);
    bool layEgg();
    bool isAlive();
};
