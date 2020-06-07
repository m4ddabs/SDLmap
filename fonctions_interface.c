#include "fonctions_interface.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Current displayed texture
extern SDL_Texture* gTextureCarte;

//Scene textures
extern LTexture gButtonTexture;
extern LTexture gMapTexture;
extern LTexture gBGville;
extern LTexture gAfficheNom;
extern LTexture gAfficheSuperficie;
extern LTexture gAfficheNbHab;
extern LTexture gAfficheCodePostal;
extern LTexture gAfficheRegion;
extern LTexture gAfficheCoordonnees;

//Font
extern TTF_Font* police;

//City
extern Ville Saint_Domingue;
extern Ville Santiago;
extern Ville San_Pedro;
extern Ville La_Romana;



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
	else if (TTF_Init()<0)
    {
        printf("Could not initialize SDL_ttf! Error : %s\n",TTF_GetError());
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
		gWindow = SDL_CreateWindow( "Carte de la Republique Dominicaine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
		police=TTF_OpenFont("imprisha.TTF",25);
	}

	return success;
}

//Initialize Texture struct
void LTextureInit(LTexture* t)
{
    //Initialize
    t->mTexture = NULL;
    t->mWidth = 0;
    t->mHeight = 0;
}

//Free Texture struct
void LTextureFree(LTexture* t)
{
    //Deallocate
    free(t);
}

//Loads image at specified path
bool loadFromFile( char* path, LTexture* t)
{
    //Get rid of preexisting texture
	freeTexture(t);

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
		else
		{
			//Get image dimensions
			t->mWidth = loadedSurface->w;
			t->mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	t->mTexture = newTexture;

	//Return success
	return t->mTexture != NULL;
}

//Deallocates texture
void freeTexture(LTexture* t)
{
    //Free texture if it exists
    if( t->mTexture != NULL )
    {
        SDL_DestroyTexture( t->mTexture );
        t->mTexture = NULL;
        t->mWidth = 0;
        t->mHeight = 0;
    }
}

//Renders texture at given point
void renderButton( int x, int y, LTexture* t )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, (t->mWidth)/16, (t->mHeight)/16 };
    SDL_RenderCopy( gRenderer, t->mTexture, NULL, &renderQuad );
}

void renderBackGround(LTexture* t )
{
    //Set rendering space and render to screen
    SDL_RenderCopy( gRenderer, t->mTexture, NULL, NULL );
}

void render_info (LTexture* t, Ville* ville, int x, int y)
{
    SDL_Rect render = {x,y,t->mWidth,t->mHeight};
    SDL_RenderCopy(gRenderer,t->mTexture,NULL,&render);
}

bool LoadTextAsTexture(char* text, LTexture* t)
{
    freeTexture(t);

    SDL_Texture* NewTexture = NULL;

    SDL_Color noir = {0,0,0};
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended( police, text , noir );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        NewTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( NewTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            t->mWidth = textSurface->w;
            t->mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    t->mTexture=NewTexture;

    //Return success
    return t->mTexture != NULL;
}

bool LoadTextVille (Ville* ville)
{
    bool success = true;
    if(!LoadTextAsTexture(ville->nom,&gAfficheNom))
    {
        printf("Could not load city's name.\n");
        success = false;
    }
    if(!LoadTextAsTexture(ville->superficie,&gAfficheSuperficie))
    {
        printf("Could not load city's area.\n");
        success = false;
    }
    if(!LoadTextAsTexture(ville->nb_hab,&gAfficheNbHab))
    {
        printf("Could not load city's nb of inhabitants.\n");
        success = false;
    }
    if(!LoadTextAsTexture(ville->code_postal,&gAfficheCodePostal))
    {
        printf("Could not load city's postal code.\n");
        success = false;
    }
    if(!LoadTextAsTexture(ville->region,&gAfficheRegion))
    {
        printf("Could not load city's region.\n");
        success = false;
    }
    if(!LoadTextAsTexture(ville->coordonnees,&gAfficheCoordonnees))
    {
        printf("Could not load city's location.\n");
        success = false;
    }
    return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Foo' texture
	if( !loadFromFile( "button.bmp", &gButtonTexture) )
	{
		printf( "Failed to load button texture image!\n" );
		success = false;
	}

	if( !loadFromFile("beige.bmp",&gBGville) )
    {
        printf("Failed to load background info texture image!\n");
        success = false;
    }

	//Load background texture
	if( !loadFromFile( "carte.bmp", &gMapTexture ) )
	{
		printf( "Failed to load map texture image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	freeTexture(&gButtonTexture);
	freeTexture(&gMapTexture);
	freeTexture(&gAfficheNom);
	freeTexture(&gAfficheSuperficie);
	freeTexture(&gAfficheNbHab);
	freeTexture(&gAfficheCodePostal);
	freeTexture(&gAfficheRegion);
	freeTexture(&gAfficheCoordonnees);

	//Close font
	TTF_CloseFont(police);

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
}

void remplir_ville (Ville* ville, FILE* fichier)
{
    if(fichier==NULL)
    {
        printf("Un probleme est survenu dans l'ouverture du fichier.\n");
        return;
    }
    fgets(ville->nom,75,fichier); //recupere le nom de la ville dans le fichier
    fgets(ville->superficie,75,fichier); //recupere la superficie
    fgets(ville->nb_hab,75,fichier); //recupere le nb d'habitants
    fgets(ville->code_postal,75,fichier); //recupere le code postal
    fgets(ville->region,75,fichier); //recupere la region
    fgets(ville->coordonnees,75,fichier); //recupere les coordonees geographiques
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

