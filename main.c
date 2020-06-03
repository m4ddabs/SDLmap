/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "fonctions_interface.h"
#include "donnees.h"




//Screen dimension constants
const int SCREEN_WIDTH =  640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gCarte = NULL;



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
		    //Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
            while(!quit)
            {
                while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
                //Apply the image
                SDL_BlitSurface( gCarte, NULL, gScreenSurface, NULL );

                //Update the surface
                SDL_UpdateWindowSurface( gWindow );

                //Wait two seconds
                SDL_Delay( 2000 );
            }

		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
