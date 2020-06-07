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

void remplir_ville (Ville* ville, FILE* fichier);

void affiche (Ville* ville);

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

//Renders the background map
void renderBackGround(LTexture* t );

//Renders the city's information
void render_info (LTexture* t, Ville* ville, int x, int y);

//Loads a text and converts it as a texture
bool LoadTextAsTexture(char* text, LTexture* t);

//Loads textures with the information of a city
bool LoadTextVille (Ville* ville);
