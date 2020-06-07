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
LTexture gSaint_Domingue;
LTexture gSantiago;
LTexture gSan_Pedro;
LTexture gLa_Romana;

//Window coordinates of the cities
const Position posstdomingue = {555, 360};
const Position possantiago = {360, 110};
const Position possanpedro = {720, 360};
const Position poslaromana = {820, 365};


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
	    //Initalizes all the texture structures
        LTextureInit(&gButtonTexture);
        LTextureInit(&gMapTexture);
        LTextureInit(&gBGville);
        LTextureInit(&gAfficheNom);
        LTextureInit(&gAfficheSuperficie);
        LTextureInit(&gAfficheNbHab);
        LTextureInit(&gAfficheCodePostal);
        LTextureInit(&gAfficheRegion);
        LTextureInit(&gAfficheCoordonnees);
        LTextureInit(&gSaint_Domingue);
        LTextureInit(&gSantiago);
        LTextureInit(&gSan_Pedro);
        LTextureInit(&gLa_Romana);


		//Load media
		if( loadMedia() )
		{
		    //Initializes all Ville Structures
		    Ville Saint_Domingue={"","","","","",""};
            Ville Santiago={"","","","","",""};
            Ville San_Pedro={"","","","","",""};
            Ville La_Romana={"","","","","",""};
            FILE* fichier1 = fopen("ville1.txt","r");
            FILE* fichier2 = fopen("ville2.txt","r");
            FILE* fichier3 = fopen("ville3.txt","r");
            FILE* fichier4 = fopen("ville4.txt","r");
            remplir_ville(&Saint_Domingue,fichier1,posstdomingue.x,posstdomingue.y);
            remplir_ville(&Santiago,fichier2,possantiago.x,possantiago.y);
            remplir_ville(&San_Pedro,fichier3,possanpedro.x,possanpedro.y);
            remplir_ville(&La_Romana,fichier4,poslaromana.x,poslaromana.y);
		    //Main loop flag
			bool quit = false;
			bool quit_info = false;

			//Event handler
			SDL_Event e;

			//Mouse position
			Position mousepos = {0,0};

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
                            SDL_GetMouseState(&(mousepos.x),&(mousepos.y));
                            printf("x = %i et y = %i\n",mousepos.x, mousepos.y);
                            //Checks if quit_info flag is set to true
                            if(quit_info)
                                {
                                    quit_info = false;
                                }
                            //event handlers for the buttons
                            ButtonEventStdomingue(&Saint_Domingue,mousepos,&e,&quit_info,&quit);
                            ButtonEventSantiago(&Santiago,mousepos,&e,&quit_info,&quit);
                            ButtonEventSanPedro(&San_Pedro,mousepos,&e,&quit_info,&quit);
                            ButtonEventLaromana(&La_Romana,mousepos,&e,&quit_info,&quit);
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
				renderButton( posstdomingue.x, posstdomingue.y, &gButtonTexture );
                //Santiago button
				renderButton( possantiago.x, possantiago.y, &gButtonTexture );
                //San Pedro de Macoris
				renderButton( possanpedro.x, possanpedro.y, &gButtonTexture );
                //La Romana
				renderButton( poslaromana.x, poslaromana.y, &gButtonTexture );

				render_text(&gSaint_Domingue,450,375);
				render_text(&gSantiago,250,81);
				render_text(&gSan_Pedro,590,320);
				render_text(&gLa_Romana,780,385);

				//Update screen
				SDL_RenderPresent( gRenderer );

            }
        }
    }


	//Free resources and close SDL
	close();

	return 0;
}
