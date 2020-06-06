#include "fonctions_interface.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//The image we will load and show on the screen
extern SDL_Surface* gCarte;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Interactive map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load stretching surface
	gCarte = loadSurface( "carte.bmp" );
	if( gCarte == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "carte.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

SDL_Surface* loadSurface( char* path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gCarte );
	gCarte = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
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

