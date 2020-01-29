#include "game.hpp"

int main(){
    Game game;
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
		//Load media
    if( !game.loadMedia("assets.png") ){
        printf( "Failed to load media!\n" );
        return 0;
    }

    game.run();
    game.close();

    return 0;
}