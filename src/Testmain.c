#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "struct.h"
#include "snake.h"
#include "jeu.h"
#include "affiche.h"
#include "collision.h"
#include "strategie.h"
#include "fruit.h"


#define NOMBRESERPENT 2


/**
 * \file Testmain.c
 * \brief permet de tester les fonctions du jeu Test la mise de fruit / les strategies Offensive Defensive / le deplacement des serpents
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
/**
 * @brief afficher_poids permet de simuler la strategie defensif pour chacun des case du plateau
 * @param s le serpent
 * @param tabsnake les snakes
 * @param nombreserpent le nombre de serpent
 * @param p le plateau
 */
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

/**
 * @brief afficher_poids permet de simuler la strategie offensif pour chacun des case du plateau
 * @param s le serpent
 * @param tabsnake les snakes
 * @param nombreserpent le nombre de serpent
 * @param p le plateau
 */
void afficher_poids_offensive(snake s,snake* tabsnake,int nombreserpent,plateau p)
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
            direction actuel =calculdirection(s.pos[0],c);
            poids = calculPoidsSerpent(c,s,tabsnake,nombreserpent,p) + calculPoidsTableau(c,p)+ calculPoidsTete(c,s,tabsnake,nombreserpent)+
                    calculStrategie(s,actuel,connaitreSnakeLePlusProche(s,tabsnake,nombreserpent));

            if(!estOccupe(c,tabsnake,nombreserpent,p))
            {
                printf("|%04d|",poids);
            }
            else
            {
                printf("| XX |");
            }

        }
        printf("\n");
    }

}

/**
 * @brief test_offensive test de la strategie
 */
void test_offensive()
{
    snake snak=init_snake(4,offensif);
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

    printf("TEST OFFENSIF\n");
    plateau* p=init_plateau(20);
    affiche(*p,s,NOMBRESERPENT);

    printf("Continuez ? \n");
    getchar();

    printf("TEST CALCUL POIDS de la strategie offensive\n");
    printf("-Plus le poids est eleve plus le serpent est attire\n");
    printf("-Le serpent cherche a attaquer le serpent adverse\n");
    printf("si un coup est strategique il obtient un grand bonus \n");
    afficher_poids_offensive(snak,s,NOMBRESERPENT,*p);

    //Pause
    printf("Continuez ? \n");
    getchar();

    printf("Le snake bouge en consequence car dans ce cas il  utilise la strategie offensive \n");


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

        afficher_poids_offensive(snak,s,NOMBRESERPENT,*p);
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


    effacer_Partie(p,s,NOMBRESERPENT);




}

/**
 * @brief test_fruit Test du placement des fruits /suppresion
 */
void test_fruit()
{
    plateau* p = init_plateau(10);

    snake* s = malloc(sizeof(snake));
    s[0] = init_snake(3,defensif);
    s[0].pos[0].x=2;s[0].pos[0].y=2;
    s[0].pos[1].x=3;s[0].pos[1].y=2;
    s[0].pos[2].x=4;s[0].pos[2].y=2;
    *(s[0].dir) = left;

   //placement fruit

   coord c1 = avoirCoordonneesLibreHasard(*p);
   ajoutFruit(c1,p);
   coord c2 = avoirCoordonneesLibreHasard(*p);
   ajoutPoison(c2,p);
   coord c3 = avoirCoordonneesLibreHasard(*p);
   ajoutTeleporter(c3,p);



   printf("TEST FRUIT\n");
   affiche(*p,s,1);
   printf("+Placement elements pos fruit: %d pos poison: %d pos teleporter :%d pos troudever [%d:%d] \n"
          ,p->cases[c1.y][c1.x],p->cases[c2.y][c2.x],p->cases[c1.y][c1.x],p->troudever[0].x,p->troudever[0].y);
   printf("Continuez ? \n");
   getchar();

   printf("+Utilisation fruit");
   //utilisation des bonus
   printf("++mangez fruit + allez a gauche\n");
   fruit_strategie(p,s,c1,left);
   printf("+++taille du serpent ? %d / ok:%d\n",s[0].taille,s[0].taille==4);
   afficher_serpent(s[0]);

   printf("++mangez poison + allez en haut \n");
   fruit_strategie(p,s,c2,up);
   printf("+++taille du serpent ? %d / ok:%d\n",s[0].taille,s[0].taille==3);
   afficher_serpent(s[0]);

   printf("++utiliser teleporter + allez en haut \n");
   coord ctrouver = p->troudever[0];
   fruit_strategie(p,s,c3,up);
   printf("+++taille du serpent ? %d / ok:%d\n",s[0].taille,s[0].taille==3);
    printf("+++position tete  est bien en hut du trou de ver  ?  ok : %d\n",(s[0].pos[0].x==ctrouver.x)&&(s[0].pos[0].y==ctrouver.y-1));
   afficher_serpent(s[0]);

   printf("+Elements sont supprimes ?  pos fruit: %d  pos poison: %d pos teleporter :%d \n"
          ,p->cases[c1.y][c1.x],p->cases[c2.y][c2.x],p->cases[c1.y][c1.x]);

   effacer_Partie(p,s,1);


   printf("Continuez ? \n");
   getchar();



   effacer_Partie(p,s,NOMBRESERPENT);



}


int main()
{
    srand(time(0));
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


    test_fruit();

    test_offensive();


    return 0;
}


