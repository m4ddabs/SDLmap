#include "fonctions_interface.h"

//Screen dimension constants
const int SCREEN_WIDTH =  1000;
const int SCREEN_HEIGHT = 600;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gButtonTexture;
LTexture gMapTexture;




int main( int argc, char* args[] )
{

	//Start up SDL and create window
	if( init() )
	{
        LTextureInit(&gButtonTexture);
        LTextureInit(&gMapTexture);

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

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background texture to screen
				renderMap( &gMapTexture );

				//Render Buttons to the screen
				renderButton( 550, 350, &gButtonTexture );

				//Update screen
				SDL_RenderPresent( gRenderer );

            }
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
