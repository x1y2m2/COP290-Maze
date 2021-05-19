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

bool quit = false;
bool pll;
bool bg = false;
bool yg = false;

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
		gWindow = SDL_CreateWindow( "Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
			pll = pl;
			cout<<pl<<"	"<<pll<<endl;
			bool** maze;
			if(pl){
				bool bbb = blue_init();
				maze = setup();
				maze_send(maze);
			}else{
				bool bbb = yellow_init();
				maze = maze_receive();
			}
			maze_setup(maze);
			
			pthread_t threads[1];
			int rc = pthread_create(&threads[0],NULL,move_recv,(void*)maze);
			
			int bdir = 1;
			int ydir = 3;
						
			//Main loop flag
			//bool quit = false;

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
						if(pl){
							blue_send(6);
						}else{
							yellow_send(6);
						}
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
									bdir = 4;
									blue_send(4);
								}else{
									xyellow--;
									ydir = 4;
									yellow_send(4);
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
									bdir = 2;
									blue_send(2);
								}else{
									xyellow++;
									ydir = 2;
									yellow_send(2);
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
									bdir = 3;
									blue_send(3);
								}else{
									yyellow--;
									ydir = 3;
									yellow_send(3);
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
									bdir = 1;
									blue_send(1);
								}else{
									yyellow++;
									ydir = 1;
									yellow_send(1);
								}
							}
							break;
							
							case SDLK_SPACE:
							if(pl){
								if(ccheck(xblue,yblue,xyellow,yyellow,bdir,maze)){
									WHITE;
									SDL_Rect rct = {12*yyellow,12*xyellow,12,12};
									SDL_RenderFillRect(gRenderer,&rct);
									if(bg){
										bwin();
										SDL_RenderPresent(gRenderer);
										quit = true;
										blue_send(5);
										SDL_Delay(10000);
									}else{
										pYellow;
										rct = {12*byellow,12*ayellow,12,12};
										SDL_RenderFillRect(gRenderer,&rct);
										xyellow = ayellow;
										yyellow = byellow;
										blue_send(5);
									}
								}
							}else{
								if(ccheck(xyellow,yyellow,xblue,yblue,ydir,maze)){
									WHITE;
									SDL_Rect rct = {12*yblue,12*xblue,12,12};
									SDL_RenderFillRect(gRenderer,&rct);
									if(yg){
										ywin();
										SDL_RenderPresent(gRenderer);
										quit = true;
										SDL_Delay(10000);
									}else{
										pBlue;
										rct = {12*bblue,12*ablue,12,12};
										SDL_RenderFillRect(gRenderer,&rct);
										xblue = ablue;
										yblue = bblue;
									}
								}
								yellow_send(5);
							}
							break;
							
							default:
							break;
						}
						if(xblue==ayellow && yblue==byellow){
							bg = true;
							pBlue;
							SDL_Rect rct = {480,0,160,SCREEN_HEIGHT/2};
							SDL_RenderFillRect(gRenderer,&rct);
						}
						if(xyellow==ablue && yyellow==bblue){
							yg = true;
							pYellow;
							SDL_Rect rct = {480,SCREEN_HEIGHT/2,160,SCREEN_HEIGHT/2};
							SDL_RenderFillRect(gRenderer,&rct);
						}
						SDL_RenderPresent(gRenderer);
					}
				}
			}
			pthread_join(threads[0],NULL);
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
	bool quite = false;
	SDL_Event e;
	int x,y;
	bool check;
	while(!quite){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&x,&y);
				quite = true;
				if(y<SCREEN_HEIGHT/2){check=true;}
				else{check=false;}
			}
		}
	}
	return check;
}

bool xcheck(int x, int y1, int y2, bool** maze){
	for(int i=y1+1;i<y2;i++){
		if(maze[i][x]){
			return false;
		}
	}
	return true;
}

bool ycheck(int x1, int x2, int y, bool** maze){
	for(int i=x1+1;i<x2;i++){
		if(maze[y][i]){
			return false;
		}
	}
	return true;
}

bool ccheck(int x1, int y1, int x2, int y2, int x, bool** maze){
	if(x==1){
		return (x1==x2) && (y1<y2) && xcheck(x1,y1,y2,maze);
	}else if(x==2){
		return (y1==y2) && (x1<x2) && ycheck(x1,x2,y1,maze);
	}else if(x==3){
		return (x1==x2) && (y1>y2) && xcheck(x1,y2,y1,maze);
	}else if(x==4){
		return (y1==y2) && (x1>x2) && ycheck(x2,x1,y1,maze);
	}
	else{return false;}
}

void bwin(){
	SDL_Rect rct = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	pBlue;
	SDL_RenderFillRect(gRenderer,&rct);
}

void ywin(){
	SDL_Rect rct = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
	pYellow;
	SDL_RenderFillRect(gRenderer,&rct);
}

void *move_recv(void *args){
	bool** maze;
	maze = (bool**)args;
	int bdir = 1;
	int ydir = 4;
	while(!quit){
		if(pll){
			int x = blue_recv();
			switch(x){
				case 1:
				if(!maze[yyellow+1][xyellow]){
					pYellow;
					SDL_Rect rct = {12*(yyellow+1),12*(xyellow),12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					WHITE;
					rct = {12*yyellow,12*xyellow,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					yyellow++;
				}
				ydir = 1;
				break;
				
				case 2:
				if(!maze[yyellow][xyellow+1]){
					pYellow;
					SDL_Rect rct = {12*(yyellow),12*(xyellow+1),12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					WHITE;
					rct = {12*yyellow,12*xyellow,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					xyellow++;
				}
				ydir = 2;
				break;
				
				case 3:
				if(!maze[yyellow-1][xyellow]){
					pYellow;
					SDL_Rect rct = {12*(yyellow-1),12*(xyellow),12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					WHITE;
					rct = {12*yyellow,12*xyellow,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					yyellow--;
				}
				ydir = 3;
				break;
				
				case 4:
				if(!maze[yyellow][xyellow-1]){
					pYellow;
					SDL_Rect rct = {12*(yyellow),12*(xyellow-1),12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					WHITE;
					rct = {12*yyellow,12*xyellow,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					xyellow--;
				}
				ydir = 4;
				break;
				
				case 5:
				if(ccheck(xyellow,yyellow,xblue,yblue,ydir,maze)){
					WHITE;
					SDL_Rect rct = {12*yblue,12*xblue,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					if(yg){
						ywin();
						SDL_RenderPresent(gRenderer);
						quit = true;
						SDL_Delay(10000);
					}else{
						pBlue;
						rct = {12*bblue,12*ablue,12,12};
						SDL_RenderFillRect(gRenderer,&rct);
						xblue = ablue;
						yblue = bblue;
					}
				}
				break;
				
				case 6:
				quit = true;
				break;
				
				default:
				break;
			}
		}else{
			int x = yellow_recv();
			switch(x){
				case 1:
				if(!maze[yblue+1][xblue]){
					pBlue;
					SDL_Rect rct = {12*(yblue+1),12*(xblue),12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					WHITE;
					rct = {12*yblue,12*xblue,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					yblue++;
				}
				bdir = 1;
				break;
				
				case 2:
				if(!maze[yblue][xblue+1]){
					pBlue;
					SDL_Rect rct = {12*(yblue),12*(xblue+1),12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					WHITE;
					rct = {12*yblue,12*xblue,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					xblue++;
				}
				bdir = 2;
				break;
				
				case 3:
				if(!maze[yblue-1][xblue]){
					pBlue;
					SDL_Rect rct = {12*(yblue-1),12*(xblue),12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					WHITE;
					rct = {12*yblue,12*xblue,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					yblue--;
				}
				bdir = 3;
				break;
				
				case 4:
				if(!maze[yblue][xblue-1]){
					pBlue;
					SDL_Rect rct = {12*(yblue),12*(xblue-1),12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					WHITE;
					rct = {12*yblue,12*xblue,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					xblue--;
				}
				bdir = 4;
				break;
				
				case 5:
				if(ccheck(xblue,yblue,xyellow,yyellow,bdir,maze)){
					WHITE;
					SDL_Rect rct = {12*yyellow,12*xyellow,12,12};
					SDL_RenderFillRect(gRenderer,&rct);
					if(bg){
						bwin();
						SDL_RenderPresent(gRenderer);
						quit = true;
						SDL_Delay(10000);
					}else{
						pYellow;
						rct = {12*byellow,12*ayellow,12,12};
						SDL_RenderFillRect(gRenderer,&rct);
						xyellow = ayellow;
						yyellow = byellow;
					}
				}
				break;
				
				case 6:
				quit = true;
				break;
				
				default:
				break;
			}
		}
		if(xblue==ayellow && yblue==byellow){
			bg = true;
			pBlue;
			SDL_Rect rct = {480,0,160,SCREEN_HEIGHT/2};
			SDL_RenderFillRect(gRenderer,&rct);
		}
		if(xyellow==ablue && yyellow==bblue){
			yg = true;
			pYellow;
			SDL_Rect rct = {480,SCREEN_HEIGHT/2,160,SCREEN_HEIGHT/2};
			SDL_RenderFillRect(gRenderer,&rct);
		}
		SDL_RenderPresent(gRenderer);
	}
	return NULL;
}
