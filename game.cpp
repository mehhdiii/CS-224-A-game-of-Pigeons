#include "game.hpp"
#include<iostream>
#include <typeinfo>
using namespace std;
#include<list>
bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "HU Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()

{
	//Loading success flag
	bool success = true;
	
	assets = loadTexture("assets.png");
    gTexture = loadTexture("hu.png");
	if(assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	//loading all music for the game:
	eggy = Mix_LoadWAV( "eggy_splash.wav" );
	background_music = Mix_LoadMUS("Waltz-music-loop/Waltz-music-loop.wav");
	bird1 = Mix_LoadWAV("Waltz-music-loop/bird1.wav");
	bird2 = Mix_LoadWAV("Waltz-music-loop/bird2.wav");
	if( eggy == NULL || background_music ==NULL || bird1==NULL || bird2==NULL)
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	//free sound:

	Mix_FreeChunk(eggy);
	Mix_FreeMusic(background_music);
	background_music =NULL;
	eggy =NULL;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

bool Game::pred(Egg * myobj, int x_check, int y_check){
	if(myobj->mover.x>x_check && myobj->mover.x < x_check+50 && myobj->mover.y>y_check && myobj->mover.y<y_check+50){
		return true;
	}
	return false;
}
void Game::updateEggs(){
	//check the collision of eggs and nests here
	//If an egg is dropped in a nest, produce a new baby pigeon
	//if the egg is dropped on floor, remove it from list.
	// if(items)
	//
	int x_range = 25;
	int y_range = 25;
	// for (list<Nest*>::iterator x = nests.begin(); x!=nests.end(); x++){
	// 	std::remove_if(eggs.begin(), eggs.end(), pred());
	// }
	list<Egg*>::iterator i = eggs.begin();
	list<Nest*>::iterator j = nests.begin();
	list<Egg*>::iterator temp;
	while(i!=eggs.end()){
		temp = i; //store the current pointer
		++i; //increment the pointer to the next object
		
		for(j = nests.begin(); j!=nests.end();j++){ //run throughout the nests list to check for collisions
			
			if((*temp)->mover.x >= (*j)->mover.x  && (*temp)->mover.x <= (*j)->mover.x+x_range && (*temp)->mover.x >= (*j)->mover.x-x_range && (*temp)->mover.y <= (*j)->mover.y+y_range && (*temp)->mover.y >= (*j)->mover.y-y_range){
				Mix_PlayChannel( -1, eggy, 0 ); //play the egg breaking sound here
				// delete *temp;
				eggs.remove(*temp);
				
				//make a new baby
				Pigeon * obj = new Pigeon(assets, true);
				obj->mover.x = (*j)->mover.x;
				obj->mover.y = (*j)->mover.y; 
				pigeons.push_back(obj);
			}
		}
		
		
		

	}
	// while (i!=eggs.end()){
	// 	if((*i)->mover.y>SCREEN_HEIGHT-50){
	// 		eggs.remove(*(i++));
	// 		break;
	// 	}
	// 	else if (i!=eggs.end()){
	// 		j = nests.begin();
	// 		while (j!=nests.end() && i!=eggs.end()){
	// 		//check for a collision:
	// 			if ( (*i)->mover.x >= (*j)->mover.x  && (*i)->mover.x <= (*j)->mover.x+x_range && (*i)->mover.x >= (*j)->mover.x-x_range && (*i)->mover.y <= (*j)->mover.y+y_range && (*i)->mover.y >= (*j)->mover.y-y_range){
	// 				Mix_PlayChannel( -1, eggy, 0 ); //play the egg breaking sound here
	// 				eggs.remove(*(i++));
	// 				// nests.remove(*(j++)); //remove the collided nest as well. or you can make the nest highlighted so that it is removed in the next collision
					
	// 				//make a new baby
	// 				Pigeon * obj = new Pigeon(assets, true);
	// 				obj->mover.x = (*j)->mover.x;
	// 				obj->mover.y = (*j)->mover.y; 
	// 				pigeons.push_back(obj);
					
					
	// 			}
				
	// 			j++;
			
		
	// 		}
		
		
		

	// }
	// else
	// 	{
	// 		break;
	// 	}
		
		

		
	// }
	// if ()

}
void Game::updatePigeons(){
	//Iterate over the link list of pigeons and generated eggs with 2% probability
	//Remove such pigeons from the list which have laid 4 eggs.
	list<Pigeon*>::iterator i = pigeons.begin();
	list<Pigeon*>::iterator temp;
	// int test = 0;
	while (i!=pigeons.end() && !pigeons.empty()){
		temp = i++;
		// cout << test++ <<endl;
		if(!(*temp)->isAlive()){
			//removing pigeon:
			pigeons.remove(*temp);
			
		}
		else{
			if(rand()%50==0 ){
				
				(*temp)->layEgg();
				Egg * newobj = new Egg(assets);
				newobj->mover.x = (*temp)->mover.x+4;
				newobj->mover.y = (*temp)->mover.y+40;
				eggs.push_back(newobj);
				
				
			}
		
		}
		// else{
		// 	Egg * myob = new Egg(assets);

		// 	myob->mover.x = (*i)->mover.x;
		// 	myob->mover.y = (*i)->mover.y;
		// }
	}
}

void Game::drawAllObjects(){
		//draw the objects here
		// list<Pigeon*>::iterator it;
		// for(it = pigeons.begin(); it!=pigeons.end(); it++){
		// 	// cout << "element" <<endl;
		// 	(*it)->draw(gRenderer);
		// }
		// for(list<Nest*>::iterator ii =  nests.begin(); ii!=nests.end(); ii++){
		// 	(*ii)->draw(gRenderer);
		// 	cout <<nests.size() <<endl;
		// }
		for(list<Unit*>::iterator ii =  items.begin(); ii!=items.end(); ii++){
			(*ii)->draw(gRenderer);
		}
		for(list<Nest*>::iterator i = nests.begin(); i!=nests.end(); i++){
			(*i)->draw(gRenderer);
		}

		for (list<Pigeon*>::iterator i = pigeons.begin(); i!=pigeons.end(); i++){
			(*i)->draw(gRenderer);
		}
		for (list<Egg*>::iterator i = eggs.begin(); i!=eggs.end(); i++){
			(*i)->draw(gRenderer);
		}
	
}

void Game::run( )
{
    SDL_RenderClear( gRenderer );
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	//play the background music
	if( Mix_PlayingMusic() == 0 )
			{
			//Play the music
			Mix_PlayMusic( background_music, 1 );
		}
	//While application is running
	while( !quit )
	{
		
		
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
				//this is a good location to add pigeon in linked list.
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse,&yMouse);
				
				if(yMouse < 300){
					// Create a new Pigeon
					Pigeon *mypigeon = new Pigeon(assets);
					if(xMouse>SCREEN_WIDTH-50){
						mypigeon->mover.x = SCREEN_WIDTH-50;
						mypigeon->mover.y = yMouse;
					}
					else{
						mypigeon->mover.x = xMouse;
						mypigeon->mover.y = yMouse;
					}				
					
					// pigeons.push_back(mypigeon);
					pigeons.push_back(mypigeon);
					// mypigeon->assets = assets;
					// SDL_RenderCopy(gRenderer, assets, NULL, NULL)
				}
				else{
					// Create a new Nest
					Nest *mynest = new Nest(assets);
					mynest->mover.x = xMouse-25;
					mynest->mover.y = yMouse-25;
					// nests.push_back(mynest);
					nests.push_back(mynest);
					// cout << "nest created!" <<endl;
				}
				
				
			}
			if (e.type == SDL_KEYDOWN){
				cout << "m pressed" <<endl;
				if( Mix_PausedMusic() == 1 )
					{
						//Resume the music
						Mix_ResumeMusic();
					}
					//If the music is playing
				else
					{
						//Pause the music
						Mix_PauseMusic();
					}
			}
		}

		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
		// SDL_RenderCopy(gRenderer, assets, NULL, NULL);
		
		updatePigeons();
		updateEggs();
		drawAllObjects();//draws all objects


		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(180);	//causes sdl engine to delay for specified miliseconds
		
	}
			
}
