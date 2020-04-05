#include "pigeon.hpp"
#include<iostream>

using namespace std;

Pigeon::Pigeon(SDL_Texture* texture ): Unit(texture), eggsLaid(0), frame(0) {
    src[0] = {0,0,160,133};
    src[1] = {0,133,160,133};
    src[2] = {0,266,160,133};
    baby = false;
    // src[3] = {226, 12, 360, 190};
    // assets = tex;

}
Pigeon::Pigeon(SDL_Texture* texture, bool baba): Unit(texture), eggsLaid(0), frame(0), baby(baba) {
    src[0] = {0,0,160,133};
    src[1] = {0,133,160,133};
    src[2] = {0,266,160,133};
    if (baby = true){
        mover.w = 10;
        mover.h = 10;
    }

    // src[3] = {226, 12, 360, 190};
    // assets = tex;

}
bool Pigeon::layEgg(){
    // SDL_RenderCopy(renderer, assets, ->, &mover);
    if (eggsLaid<4){
        eggsLaid++;
        return true;
    }
    else
        // eggsLaid++;
        return false;
}
void Pigeon::draw(SDL_Renderer * renderer){
    // cout << "drawing pigeon" <<endl;
    if (baby = true){
        if (mover.w<50){
            mover.w+=2;
            mover.h+=2;
        }
        else{
            baby = false;
        }
    }
    SDL_RenderCopy(renderer, assets, &src[frame], &mover);
    frame++;
    if (frame==3) frame = 0; 
    if (mover.x<SCREEN_WIDTH-50){
        mover.x+=5;
    }
    

    if (mover.y >50 ){
        //speed 1x
        mover.y-=2;
    }


    //moving down with 20% probability
    // else {/*if (mover.y&& rand()%8 ==0){*/ //set and condition for return journey
    //     cout << "running" <<endl;
    //     mover.y+=5;
    // }
    // }
    // if(layEgg()){
    //     mover.y+=20;
    //     SDL_RenderCopy(renderer, assets, &src[3], &mover);
    //     mover.y-=20;
    // }
}

bool Pigeon::isAlive(){
    // return layEgg();
    return (eggsLaid<4);

}

Pigeon::~Pigeon(){
    eggsLaid = 0;
    src[0] = {0, 0, 0, 0};
    src[1] = {0, 0, 0, 0};
    src[2] = {0, 0, 0, 0};
}