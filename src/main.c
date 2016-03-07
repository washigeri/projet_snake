#include "struct.h"
#include "jeu.h"
#include "snake.h"
#include "affiche.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    snake snak=init_snake(4);
    snak.pos[0].x=10;snak.pos[0].y=10;
    snak.pos[1].x=9;snak.pos[1].y=10;
    snak.pos[2].x=8;snak.pos[2].y=10;
    snak.pos[3].x=7;snak.pos[3].y=10;
    snake schlanga=init_snake(4);
    schlanga.pos[0].x=15;schlanga.pos[0].y=10;
    schlanga.pos[1].x=16;schlanga.pos[1].y=10;
    schlanga.pos[2].x=17;schlanga.pos[2].y=10;
    schlanga.pos[3].x=18;schlanga.pos[3].y=10;
    schlanga.dir[0]=left;
    snake* s=(snake*) malloc (2*sizeof(snake));
    s[0]=snak;
    s[1]=schlanga;
    plateau p=init_plateau(30);
    affiche(p,s,2);
    while(!jouer(s,2,p)){
        affiche(p,s,2);
    }
    return 0;
}
