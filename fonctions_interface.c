#include "fonctions_interface.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Current displayed texture
extern SDL_Texture* gTextureCarte;






bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTextureCarte = loadTexture( "carte.bmp" );
	if( gTextureCarte == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}


SDL_Texture* loadTexture( char* path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s!\n", path);
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}



void close()
{
    //Free loaded image
    SDL_DestroyTexture( gTextureCarte );
    gTextureCarte = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    //IMG_Quit();
    SDL_Quit();
}


void remplir_ville (Ville* ville, FILE* fichier)
{
    if(fichier==NULL)
    {
        printf("Un probleme est survenu dans l'ouverture du fichier.\n");
        return;
    }
    fgets(ville->nom,50,fichier); //recupere le nom de la ville dans le fichier
    fgets(ville->superficie,50,fichier); //recupere la superficie
    fgets(ville->nb_hab,50,fichier); //recupere le nb d'habitants
    fgets(ville->code_postal,50,fichier); //recupere le code postal
    fgets(ville->region,50,fichier); //recupere la region
    fgets(ville->coordonnees,50,fichier); //recupere les coordonees geographiques
}

void affiche (Ville* ville)
{
    printf("nom : %s",ville->nom);
    printf("superficie : %s",ville->superficie);
    printf("nb hab : %s",ville->nb_hab);
    printf("code postal : %s",ville->code_postal);
    printf("region : %s",ville->region);
    printf("coordonnees : %s\n\n",ville->coordonnees);
}

