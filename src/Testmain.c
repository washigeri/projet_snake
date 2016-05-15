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
#include "jeu.h"
#include "affiche.h"
#include "collision.h"
#include "strategie.h"


#define NOMBRESERPENT 2


/**
 * \file Testmain.c
 * \brief permet de tester les fonctions du jeu
 *
 */

/**
 * @brief afficher_serpent afficher les coordonnes des serpents
 * @param s le serpent
 */
void afficher_serpent(snake s)
{
    int i;

    printf("-Serpent \n");
    for(i = 0; i < s.taille;i++)
    {
        printf("--[%d,%d]\n",s.pos[i].x,s.pos[i].y);
    }
}

void afficher_collision(plateau p,snake* s,int n)
{
    bools* bs = collisions(p,s,n);

    int i;
    for(i = 0 ; i < n; i++)
    {
        printf("collision serpent %d ? => %d \n ",i,!bs[i].b);
    }

    free(bs);
}

void afficher_poids(snake s,snake* tabsnake,int nombreserpent,plateau p)
{
    int i,j;
    int poids =0;
    for(i=0;i < p.taille;i++)
    {
        for(j=0;j< p.taille;j++)
        {
            coord c;
            c.x = j;
            c.y = i;
            poids = calculPoidsSerpent(c,s,tabsnake,nombreserpent,p) + calculPoidsTableau(c,p);

            if(!estOccupe(c,tabsnake,nombreserpent,p))
            {
                printf("|%03d|",poids);
            }
            else
            {
                printf("| X |");
            }

        }
        printf("\n");
    }

}


int main()
{
    /*Creation des serpent*/
    snake snak=init_snake(4,defensif);
    snak.pos[0].x=10;snak.pos[0].y=10;
    snak.pos[1].x=9;snak.pos[1].y=10;
    snak.pos[2].x=8;snak.pos[2].y=10;
    snak.pos[3].x=7;snak.pos[3].y=10;
    *(snak.dir) = right;


    snake schlanga=init_snake(4,defensif);
    schlanga.pos[0].x=15;schlanga.pos[0].y=15;
    schlanga.pos[1].x=16;schlanga.pos[1].y=15;
    schlanga.pos[2].x=17;schlanga.pos[2].y=15;
    schlanga.pos[3].x=18;schlanga.pos[3].y=15;
    schlanga.dir[0]=left;
    snake* s=(snake*) malloc (NOMBRESERPENT*sizeof(snake));
    s[0]=snak;
    s[1]=schlanga;



    printf("TEST DE BASE\n");
    plateau* p=init_plateau(20);
    affiche(*p,s,NOMBRESERPENT);

    printf("Serpent de base\n");
    afficher_serpent(snak);



    //Pause

    printf("Continuez ? \n");
    getchar();

    /*Test Avancer*/

    movesnake(snak,right);
    affiche(*p,s,NOMBRESERPENT);
    printf("TEST MOUVEMENT\n");
    printf("+Test Avancer dans la direction courante aller a droite (tout droit)\n");
    afficher_serpent(snak);


    //Pause

    printf("Continuez ? \n");
    getchar();


    movesnake(snak,left);
    affiche(*p,s,NOMBRESERPENT);
    printf("+Test Avancer dans la direction contraire\n");
    printf("le serpent ignore la direction et avance dans la direction courante\n");
    afficher_serpent(snak);


    //Pause

    printf("Continuez ? \n");
    getchar();

    printf("+Test Tourner\n");
    movesnake(snak,up);
    affiche(*p,s,NOMBRESERPENT);
    printf("+Test Tourner aller en haut\n");
    afficher_serpent(snak);


    //Pause
    printf("Continuez ? \n");
    getchar();

    printf("TEST CALCUL POIDS de la strategie defensive\n");
    printf("-Plus le poids est eleve plus le serpent est attire\n");
    printf("-Ainsi les poids du cote bas droit sont les plus faible car\n");
    printf(" ils contiennent un serpent et sont proches des murs\n");
    afficher_poids(snak,s,NOMBRESERPENT,*p);

    //Pause
    printf("Continuez ? \n");
    getchar();

    printf("Le snake bouge en consequence car dans ce cas il  utilise la strategie defensive \n");


    printf("Continuez ? \n");
    getchar();

    int i;
    for(i = 0; i < 15 ; i++)
    {
        movesnake(snak,choix_strategie(snak,s,NOMBRESERPENT,*p,left));
        movesnake(schlanga,left);
        printf("\n");
        affiche(*p,s,NOMBRESERPENT);

        printf("pas = %d \n",i);
        printf("le Schalanga avance tout droit ( a droite) \n");

        afficher_poids(snak,s,NOMBRESERPENT,*p);
        afficher_collision(*p,s,NOMBRESERPENT);


        if(i < 14)
        {

            printf("Incrementer le pas ? \n");
            getchar();
        }
        else
        {
            printf("Terminer la simulation ? \n");
            getchar();

        }


    }

    printf("Collision\n");
    afficher_collision(*p,s,NOMBRESERPENT);

    printf("Fin ? \n");
    getchar();

    effacer_Partie(p,s,NOMBRESERPENT);

    return 0;
}


