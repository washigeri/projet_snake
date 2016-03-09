#include "struct.h"
#include "jeu.h"
#include "snake.h"
#include "affiche.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
/*LE SNAKE*/
    snake snak=init_snake(4,joueur);
    snak.pos[0].x=10;snak.pos[0].y=10;
    snak.pos[1].x=9;snak.pos[1].y=10;
    snak.pos[2].x=8;snak.pos[2].y=10;
    snak.pos[3].x=7;snak.pos[3].y=10;
/*LE SCHLANGA*/ 
   snake schlanga=init_snake(4,idle);
    schlanga.pos[0].x=15;schlanga.pos[0].y=20;
    schlanga.pos[1].x=16;schlanga.pos[1].y=20;
    schlanga.pos[2].x=17;schlanga.pos[2].y=20;
    schlanga.pos[3].x=18;schlanga.pos[3].y=20;
    schlanga.dir[0]=left;
    snake* s=(snake*) malloc (2*sizeof(snake));
    s[0]=snak;
    s[1]=schlanga;

/*INITILAISATION*/
	/*DEBUT DU JEU*/

	system("clear");
	int taille_plateau=0;
	printf("\n****LE JEU VA COMMENCER****\n\n");
	printf("\nSaisissez la taille_plateau du tableau (minimum 20x20) puis ENTER\n");

	scanf("%d",&taille_plateau);
	while( taille_plateau<=19 ){printf("\nResaisissez la taille_plateau:");scanf("%d",&taille_plateau);}

	printf("\nReady!\n");
	printf("Pour se deplacer: appuyer sur z,q,s et d\n");
	system("sleep 1;clear");

    plateau p=init_plateau(taille_plateau);
    affiche(p,s,2);

/*JEU*/
    while(!jouer(s,2,p)){
        affiche(p,s,2);
    }
    return 0;
}
