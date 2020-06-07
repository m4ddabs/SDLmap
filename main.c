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
LTexture gBGville;
LTexture gAfficheNom;
LTexture gAfficheSuperficie;
LTexture gAfficheNbHab;
LTexture gAfficheCodePostal;
LTexture gAfficheRegion;
LTexture gAfficheCoordonnees;


//Font
TTF_Font* police = NULL;

//City
Ville Saint_Domingue;
Ville Santiago;
Ville San_Pedro;
Ville La_Romana;


int main( int argc, char* args[] )
{

	//Start up SDL and create window
	if( init() )
	{
        LTextureInit(&gButtonTexture);
        LTextureInit(&gMapTexture);
        LTextureInit(&gBGville);
        LTextureInit(&gAfficheNom);
        LTextureInit(&gAfficheSuperficie);
        LTextureInit(&gAfficheNbHab);
        LTextureInit(&gAfficheCodePostal);
        LTextureInit(&gAfficheRegion);
        LTextureInit(&gAfficheCoordonnees);

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
            LoadTextVille(&Saint_Domingue);
            LoadTextVille(&Santiago);
            LoadTextVille(&San_Pedro);
            LoadTextVille(&La_Romana);
		    //Main loop flag
			bool quit = false;
			bool quit_info = false;

			//Event handler
			SDL_Event e;

            while(!quit)
            {
                while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					switch(e.type)
					{
						case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_MOUSEBUTTONUP:
                            while(!quit_info)
                            {
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );
                                renderBackGround(&gBGville);
                                render_info(&gAfficheNom,&Santiago,0,0);
                                render_info(&gAfficheSuperficie,&Santiago,0,50);
                                render_info(&gAfficheNbHab,&Santiago,0,100);
                                render_info(&gAfficheCodePostal,&Santiago,0,150);
                                render_info(&gAfficheCoordonnees,&Santiago,0,200);
                                SDL_RenderPresent(gRenderer);
                                SDL_WaitEvent(&e);
                                if(e.type==SDL_MOUSEBUTTONDOWN)
                                    quit_info=true;
                            }
                            break;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background texture to screen
				renderBackGround( &gMapTexture );

				//Render Buttons to the screen

				//Santo Domingo Button
				renderButton( 555, 360, &gButtonTexture );
                //Santiago button
				renderButton( 360, 110, &gButtonTexture );
                //San Pedro de Macoris
				renderButton( 720, 360, &gButtonTexture );
                //La Romana
				renderButton( 820, 365, &gButtonTexture );

				//Update screen
				SDL_RenderPresent( gRenderer );

            }
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
