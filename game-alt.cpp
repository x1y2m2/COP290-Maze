#include "game-alt.h"

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
			bool pl = entry();
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
						int s,t;
						if(pl){
							pBlue;
							s = xblue;
							t = yblue;
						}else{
							pYellow;
							s = xyellow;
							t = yyellow;
						}
						switch(e.key.keysym.sym)
						{
							case SDLK_UP:
							if(!maze[t][s-1]){
								SDL_Rect rct = {12*(t),12*(s-1),12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								WHITE;
								rct = {12*t,12*s,12,12};
								if(pl){
									xblue--;
								}else{
									xyellow--;
								}
								SDL_RenderFillRect(gRenderer,&rct);
							}
							break;
							
							case SDLK_DOWN:
							if(!maze[t][s+1]){
								SDL_Rect rct = {12*(t),12*(s+1),12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								WHITE;
								rct = {12*t,12*s,12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								if(pl){
									xblue++;
								}else{
									xyellow++;
								}
							}
							break;
							
							case SDLK_LEFT:
							if(!maze[t-1][s]){
								SDL_Rect rct = {12*(t-1),12*(s),12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								WHITE;
								rct = {12*t,12*s,12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								if(pl){
									yblue--;
								}else{
									yyellow--;
								}
							}
							break;
							
							case SDLK_RIGHT:
							if(!maze[t+1][s]){
								SDL_Rect rct = {12*(t+1),12*(s),12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								WHITE;
								rct = {12*t,12*s,12,12};
								SDL_RenderFillRect(gRenderer,&rct);
								if(pl){
									yblue++;
								}else{
									yyellow++;
								}
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

bool entry(){
	pBlue;
	SDL_Rect rct = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_RenderFillRect(gRenderer, &rct);
	pYellow;
	rct = {0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_RenderFillRect(gRenderer, &rct);
	SDL_RenderPresent(gRenderer);
	bool quit = false;
	SDL_Event e;
	int x,y;
	bool check;
	while(!quit){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&x,&y);
				quit = true;
				if(y<SCREEN_HEIGHT/2){check=true;}
				else{check=false;}
			}
		}
	}
	return check;
}
