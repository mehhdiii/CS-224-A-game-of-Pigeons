#include "game.hpp"

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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

void Game::checkCollision(){
	for (auto itEgg = eggs.cbegin(); itEgg != eggs.end(); itEgg++){
	for (auto itNest = nests.cbegin(); itNest != nests.end(); itNest++){
		SDL_Rect eggMover = (*itEgg)->getMover();
		SDL_Rect nestMover = (*itNest)->getMover();

		
		if(nestMover.x < eggMover.x && eggMover.x < nestMover.x + nestMover.w  && eggMover.y > nestMover.y){
			pigeons.push_back(new Pigeon(assets,eggMover, true));
			delete (*itEgg);
			eggs.erase(itEgg--);
			break;
		}

	}	
}
}
void Game::update(){

	for (auto itr = pigeons.cbegin(); itr != pigeons.end(); itr++){
		if(rand()%100 < 2){
			if((*itr)->layEgg())			
				eggs.push_back(new Egg(assets, (*itr)->getMover()));
		}
	}

	for (auto itr = pigeons.cbegin(); itr != pigeons.end(); itr++){
		if ((*itr)->isAlive()) {
			delete (*itr);
			pigeons.erase(itr--);
		}
	}
	for (auto itr = eggs.cbegin(); itr != eggs.end(); itr++){
		if ((*itr)->dropped()) {
			delete (*itr);
			eggs.erase(itr--);
		}		
	}

	checkCollision();
}

void Game::drawAllObjects(){
		//draw the objects here
	for(auto p: pigeons)
		p->draw(gRenderer);	//draws object on renderer
	for (auto n: nests)
		n->draw(gRenderer);
	for (auto e: eggs)
		e->draw(gRenderer);
}

void Game::run( )
{
    SDL_RenderClear( gRenderer );
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	// Pigeon pigeons[10];

	

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
					SDL_Rect rect={xMouse-25, yMouse-25, 50, 50};
					pigeons.push_back(new Pigeon(assets, rect));
				}
				else{
					SDL_Rect rect={xMouse-25, yMouse-25, 50, 50};
					nests.push_back(new Nest(assets, rect));
				}
				break;
			}
		}
		update();// updates the objects for possible new eggs and baby pigeons.

		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer

		drawAllObjects();//draws all objects

		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
		
	}
			
}
