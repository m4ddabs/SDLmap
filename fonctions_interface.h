#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include<string.h>
#include "donnees.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

struct LTexture
{
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

typedef struct LTexture LTexture;

//Frees media and shuts down SDL
void close();

//stocks text from file in the different fields of structure ville
void remplir_ville (Ville* ville, FILE* fichier,int posx, int posy);

//Initialize Texture struct
void LTextureInit(LTexture* t);

//Free Texture struct
void LTextureFree(LTexture* t);

//Loads image at specified path
bool loadFromFile( char* path, LTexture* t );

//Deallocates texture
void freeTexture(LTexture* t);

//Renders texture at given point
void renderButton( int x, int y, LTexture* t );

//Renders the background
void renderBackGround(LTexture* t );

//Renders the city's information
void render_text (LTexture* t, int x, int y);

//Loads a text and converts it as a texture
bool LoadTextAsTexture(char* text, LTexture* t);

//Loads textures with the information of a city
bool LoadTextVille (Ville* ville);

//This function handles the event of the Saint domingue button being pressed
void ButtonEventStdomingue(Ville* ville, Position mousepos, SDL_Event* e, bool* quit_info, bool* quit);

//This function handles the event of the Santiago button being pressed
void ButtonEventSantiago(Ville* ville, Position mousepos, SDL_Event* e, bool* quit_info, bool* quit);

//This function handles the event of the San Pedro de macoris button being pressed
void ButtonEventSanPedro(Ville* ville, Position mousepos, SDL_Event* e, bool* quit_info, bool* quit);

//This function handles the event of the La Romana button being pressed
void ButtonEventLaromana(Ville* ville, Position mousepos, SDL_Event* e, bool* quit_info, bool* quit);
