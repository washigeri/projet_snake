#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "struct.h"
#include "snake.h"
#include "affiche.h"


#define NOMBRESERPENT 2

int main()
{
 /*Creation des serpent*/
    snake snak=init_snake(4,joueur);
    snak.pos[0].x=10;snak.pos[0].y=10;
    snak.pos[1].x=9;snak.pos[1].y=10;
    snak.pos[2].x=8;snak.pos[2].y=10;
    snak.pos[3].x=7;snak.pos[3].y=10;
    *(snak.dir) = left;


    snake schlanga=init_snake(4,defensif);
    schlanga.pos[0].x=15;schlanga.pos[0].y=15;
    schlanga.pos[1].x=16;schlanga.pos[1].y=15;
    schlanga.pos[2].x=17;schlanga.pos[2].y=15;
    schlanga.pos[3].x=18;schlanga.pos[3].y=15;
    schlanga.dir[0]=left;
    snake* s=(snake*) malloc (NOMBRESERPENT*sizeof(snake));
    s[0]=snak;
    s[1]=schlanga;


    plateau p=init_plateau(taille_plateau);
    affiche(p,s,NOMBRESERPENT);



    /*Test Avancer*/
    printf("TEST MOVEMENT ");
    printf("+Test Avancer dans la direction courant\n");
    afficher_serpent(&snak);
    movesnake(snak,left);
    affiche(p,s,NOMBRESERPENT);
    afficher_serpent(&snak);

    printf("+Test Avancer dans la direction contraire\n");
    afficher_serpent(&snak);
    movesnake(snak,right);
    affiche(p,s,NOMBRESERPENT);
    afficher_serpent(&snak);


    printf("+Test Tourner\n");
    afficher_serpent(&snak);
    movesnake(snak,right);
    affiche(p,s,NOMBRESERPENT);
    afficher_serpent(&snak);


    printf("TEST CALCULPOIDS\n");
    afficher_poids(snak,s,NOMBRESERPENT,p);

}


void afficher_serpent(snake* s)
{
    int i;

    printf("-Serpent %p \n",s);
    for(i = 0; i < s.taille;i++)
    {
        printf("--[%d,%d]\n",s->pos[i].x,s->pos[i].y);
    }
}

void afficher_poids(snake s,snake* tabsnake,int nombreserpent,plateau p)
{
    int i,j;
    int poids =0;
    for(i=0;i < p->taille;i++)
    {
        for(j=0;j< p->taille;j++)
        {
            coord c;
            c.x = i;
            c.y = j;
            poids = calculPoidsSerpent(c,s,tabsnake,nombreserpent,p) + calculPoidsTableau(c,p);

            printf("| %d |",poids);

        }
        printf("/n");
    }

}
