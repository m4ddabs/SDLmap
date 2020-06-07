#include<stdlib.h>
#include <stdio.h>

//Coordinate system for the window
struct Position
{
    int x;
    int y;
};

typedef struct Position Position;


struct Ville
{
    char nom[75];
    char superficie[75];
    char nb_hab[75];
    char code_postal[75];
    char region[75];
    char coordonnees[75];
    Position buttonpos;
};
typedef struct Ville Ville;




