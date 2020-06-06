#include "fonctions_interface.h"

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
	if( init() )
	{
		//Load media
		if( loadMedia() )
		{
		    Ville Saint_Domingue={"","","","","",""};
            Ville Santiago={"","","","","",""};
            Ville San_Pedro={"","","","","",""};
            Ville La_Romana={"","","","","",""};
            FILE* fichier1 = fopen("ville1.txt","r");
            FILE* fichier2 = fopen("ville2.txt","r");
            FILE* fichier3 = fopen("ville3.txt","r");
            FILE* fichier4 = fopen("ville4.txt","r");
            remplir_ville(&Saint_Domingue,fichier1);
            remplir_ville(&Santiago,fichier2);
            remplir_ville(&San_Pedro,fichier3);
            remplir_ville(&La_Romana,fichier4);
            affiche(&Saint_Domingue);
            affiche(&Santiago);
            affiche(&San_Pedro);
            affiche(&La_Romana);
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

                //Apply the image stretched
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled( gCarte, NULL, gScreenSurface, &stretchRect );

                //Update the surface
                SDL_UpdateWindowSurface( gWindow );
            }
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
