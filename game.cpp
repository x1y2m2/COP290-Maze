#include "game.h"

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

int xblue, yblue, xyellow, yyellow;
int ablue, bblue, ayellow, byellow;

using namespace std;

bool init()
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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
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

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			bool** maze = setup();
			maze_setup(maze);
						
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
					else if(e.type == SDL_KEYDOWN)
					{
						switch(e.key.keysym.sym)
						{
							case SDLK_UP:
							if(!maze[yblue][xblue-1]){
								pBlue;
								SDL_Rect rct = {12*yblue,12*(xblue-1),12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								WHITE;
								rct = {12*yblue,12*xblue,12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								xblue--;
							}
							break;
							
							case SDLK_DOWN:
							if(!maze[yblue][xblue+1]){
								pBlue;
								SDL_Rect rct = {12*(yblue),12*(xblue+1),12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								WHITE;
								rct = {12*yblue,12*xblue,12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								xblue++;
							}
							break;
							
							case SDLK_LEFT:
							if(!maze[yblue-1][xblue]){
								pBlue;
								SDL_Rect rct = {12*(yblue-1),12*(xblue),12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								WHITE;
								rct = {12*yblue,12*xblue,12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								yblue--;
							}
							break;
							
							case SDLK_RIGHT:
							if(!maze[yblue+1][xblue]){
								pBlue;
								SDL_Rect rct = {12*(yblue+1),12*(xblue),12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								WHITE;
								rct = {12*yblue,12*xblue,12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								yblue++;
							}
							break;
							
							default:
							break;
						}
						SDL_RenderPresent(gRenderer);
											}
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

void maze_setup(bool** maze){
	//Start up SDL and create window
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render red filled quad
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			SDL_Rect fillRect = {12*i,12*j,12,12};
			if(maze[i][j]){
				SDL_RenderFillRect(gRenderer,&fillRect);
			}
		}
	}

	//Update screen
	pBlue;
	SDL_Rect rct = {12,12,12,12};
	SDL_RenderFillRect(gRenderer,&rct);
	int x = WIDTH-2;
	int y = HEIGHT-2;
	while(maze[y][x]){
		x--;
	}
	rct = {12*y,12*x,12,12};
	pYellow;
	SDL_RenderFillRect(gRenderer, &rct);
	SDL_RenderPresent(gRenderer);
	xblue = 1;
	yblue = 1;
	xyellow = x;
	yyellow = y;
	ablue = 1;
	bblue = 1;
	ayellow = x;
	byellow = y;
}
