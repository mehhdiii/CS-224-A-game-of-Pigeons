#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>

#include "pigeon.hpp"
#include "egg.hpp"
#include "nest.hpp"
using namespace std;

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;

    //You may use C++ linked lists, or you can create your own.

    

    list<Unit*> items;   
    list <Pigeon*> pigeons;
    list<Egg*> eggs;
    list<Nest*> nests;

    //sound variables:
    Mix_Chunk *eggy = NULL; //egg splash.
    Mix_Music *background_music = NULL; //plays in the background
    Mix_Chunk *bird1 = NULL;
    Mix_Chunk *bird2 = NULL;
public:

    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
    void updateEggs();
    void updatePigeons();
    void drawAllObjects();
};

