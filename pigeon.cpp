#include "pigeon.hpp"
#include<iostream>

using namespace std;

Pigeon::Pigeon(SDL_Texture* texture ): Unit(texture){
    src[0] = {0,0,160,133};
    src[1] = {0,133,160,133};
    src[2] = {0,266,160,133};
    // src[3] = {226, 12, 360, 190};
    // assets = tex;

}
bool Pigeon::layEgg(){
    // SDL_RenderCopy(renderer, assets, ->, &mover);
    if (eggsLaid<4)
        return true;
    else
        return false;
}
void Pigeon::draw(SDL_Renderer * renderer){
    // cout << "drawing pigeon" <<endl;
    SDL_RenderCopy(renderer, assets, &src[frame], &mover);
    frame++;
    if (frame==3) frame = 0;
    mover.x+=5;
    //moving up with 50% probability
    if (mover.y >50 ){
        //speed 1x
        mover.y-=2;
    }

    if (layEgg()){
        Egg * myob = new Egg(assets);
        myob->mover.x = mover.x;
        myob->mover.y = mover.y;
        myob->draw(renderer);
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

Pigeon::~Pigeon(){

}