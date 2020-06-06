#include "fonctions_interface.h"

//Screen dimension constants
const int SCREEN_WIDTH =  640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;



//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTextureCarte = NULL;




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

				//Clear screen
				SDL_RenderClear( gRenderer );

				//Render texture to screen
				SDL_RenderCopy( gRenderer, gTextureCarte, NULL, NULL );

				//Update screen
				SDL_RenderPresent( gRenderer );

            }
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
