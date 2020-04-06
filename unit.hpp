#include "SDL.h"
#pragma once
class Unit{
protected:
    SDL_Texture* assets;
    SDL_Rect src;
    SDL_Rect mover = {0,0,50,50};
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
public:
    Unit(SDL_Texture*);
    virtual void draw(SDL_Renderer*) = 0;
    SDL_Rect getMover();
    // bool operator>=(Unit*);
    // bool operator<=(Unit*);
    // bool operator==(Unit*);
    // Unit* operator+(int);
    void setCoordinates(int, int);
    virtual ~Unit();
};