#include "fonctions_interface.h"
#include "donnees.h"

void afficher_carte(SDL_Surface* carte, SDL_Surface* ecran, TTF_Font* police)
{
    carte = SDL_LoadBMP("carte.bmp");
    if (!carte)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Rect posCarte;
    posCarte.x=0;
    posCarte.y=0;
    SDL_Rect postexte;
    postexte.x=0;
    postexte.y=0;
    SDL_Color noir = {0,0,0};
    SDL_Surface* texte = TTF_RenderText_Blended(police,"coucouille",noir);
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        continuer=0;
                        break;
                }
                break;
        }
        SDL_BlitSurface(carte,NULL,ecran,&posCarte);
        SDL_BlitSurface(texte,NULL,ecran,&postexte);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(texte);
}
