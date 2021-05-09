#include "setup.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

void maze_setup(bool** maze);

//Frees media and shuts down SDL
void close();

bool xcheck(int x, int y1, int y2);
bool ycheck(int x1, int x2, int y);
bool ccheck(int x1, int y1, int x2, int y2, int x);
