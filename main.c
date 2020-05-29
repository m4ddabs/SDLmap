#include<stdlib.h>
#include<stdio.h>
#include<SDL.h>
#include <SDL_ttf.h>
#include "fonctions_interface.h"

int main ( int argc, char** argv )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);
    if (TTF_Init()==-1)
    {
        fprintf(stderr,"Erreur d'initialisation de TTF_Init : %s\n",TTF_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetIcon(SDL_LoadBMP("insa-cvl.bmp"),NULL);
    SDL_Surface* ecran = SDL_SetVideoMode(1190, 810, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !ecran )
    {
        printf("Unable to set 1190x810 video: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* carte;
    SDL_WM_SetCaption("Carte interactive de la Republique Dominicaine",NULL);
    TTF_Font* police = TTF_OpenFont("imprisha.ttf",65);
    afficher_carte(carte,ecran,police);
    TTF_CloseFont(police);
    SDL_FreeSurface(carte);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
