#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define WIDTH 40
#define HEIGHT 40

#define WHITE SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF )
#define pBlue SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF )
#define pYellow SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF )
