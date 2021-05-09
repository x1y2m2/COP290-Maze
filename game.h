#include "setup.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

void maze_setup(bool** maze);

//Frees media and shuts down SDL
void close();

bool entry();
