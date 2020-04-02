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
	if( SDL_Init( SDL_INIT_VIDEO /*| SDL_INIT_AUDIO*/ ) < 0 )
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

	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	
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

void Game::updateEggs(){
	//check the collision of eggs and nests here
	//If an egg is dropped in a nest, produce a new baby pigeon
	//if the egg is dropped on floor, remove it from list.
}
void Game::updatePigeons(){
	//Iterate over the link list of pigeons and generated eggs with 2% probability
	//Remove such pigeons from the list which have laid 4 eggs.
	for (list<Pigeon*>::iterator i = pigeons.begin(); i!=pigeons.end(); i++){
		if(!((*i)->isAlive())){
			pigeons.pop_back();
		}
		else{
			(*i)->layEgg();
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
		for (list<Pigeon*>::iterator i = pigeons.begin(); i!=pigeons.end(); i++){
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
					
					mypigeon->mover.x = xMouse;
					mypigeon->mover.y = yMouse;
					// pigeons.push_back(mypigeon);
					pigeons.push_back(mypigeon);
					// mypigeon->assets = assets;
					// SDL_RenderCopy(gRenderer, assets, NULL, NULL)
				}
				else{
					// Create a new Nest
					Nest *mynest = new Nest(assets);
					
					mynest->mover.x = xMouse-20;
					mynest->mover.y = yMouse-20;
					// nests.push_back(mynest);
					items.push_back(mynest);
					// cout << "nest created!" <<endl;
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
		SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
		
	}
			
}
