#include <SDL.h>
#include <stdbool.h>
#include<string.h>
#include<stdlib.h>

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Loads individual image
SDL_Surface* loadSurface( char* path );

//Frees media and shuts down SDL
void close();


