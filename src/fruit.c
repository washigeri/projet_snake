#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include "struct.h"
#include "snake.h"
#include "fruit.h"


/*la chance de spawn dun objet a cahque tour */
#define CH_SPAWNFRUIT 50 //sur 100

/*le nombre maximum de bonus sur le plateau*/
#define MAX_NB_ITEM 100
/*le nombre maximum de teleporter et de trou de ver*/
#define MAX_TELEPORT 3
/*le nombre de type dobjet troudever non compris*/
#define NB_TYPE_ITEM 3

/*la marge d'apparition des trou de ver*/
#define MARGE 5
/** Gestion des Bonus
 * */

/**
 * @brief avoirCoordonneesLibreHasard Permet de trouver un coordonnees libre sur le plateau de jeu (serpents exclus)
 * @param plat le plateau de jeu
 * @return une coordonnee libre
 */
coord avoirCoordonneesLibreHasard(plateau plat)
{
    coord c;
    int x,y;
    do{

        x = rand() % plat.taille;
        y = rand() % plat.taille;


        c.x = x;
        c.y = y;



    }while(plat.cases[y][x] > 0);

    return c;
}
/**
 * @brief avoirCoordonneesLibreHasardAvecMarge Permet de trouver un coordonnees libre sur le plateau de jeu avec une marge dexclusion (serpents exclus)
 * @param plat le plateau de jeu
 * @return une coordonnee libre
 */
coord avoirCoordonneesLibreHasardAvecMarge(plateau plat)
{
    coord c;
    int x,y;
    do{

        x = (rand() % (plat.taille-MARGE)) + MARGE;
        y = (rand() % (plat.taille-MARGE)) + MARGE;


        c.x = x;
        c.y = y;



    }while(plat.cases[y][x] > 0);

    return c;
}


/**
 * @brief ajoutFruit permet d'ajouter un fruit sur le plateau le fruit faire grandir le serpent
 * @param cor la cordonnee du fruit
 * @param plat le plateau
 */
void ajoutFruit(coord cor,plateau* plat)
{
    if(plat->cases[cor.y][cor.x] == 0)
    {
        plat->cases[cor.y][cor.x] = 2;
        plat->nombreItem++;
    }

}
/**
 * @brief ajoutFruit permet d'ajouter un poison sur le plateau le poison reduit la taille du serpent
 * @param cor la cordonnee du poisson
 * @param plat le plateau
 */
void ajoutPoison(coord cor,plateau* plat)
{
    if(plat->cases[cor.y][cor.x] == 0)
    {
        plat->cases[cor.y][cor.x] = 3;
        plat->nombreItem++;
    }

}

/**
 * @brief creationTroudever permet la creation d'un troudever sur le plateau les trou de ver son la porte de sortie
 * dun teleporter
 * @param p le plateau
 */
void creationTroudever(plateau* p)
{

     coord c = avoirCoordonneesLibreHasardAvecMarge(*p);

    p->nombreTroudever++;

    if(p->nombreTroudever == 0)
    {
        p->troudever = malloc(sizeof(coord));
        p->troudever[0] = c;
    }
    else
    {
        coord * newtab = malloc(sizeof(coord)*p->nombreTroudever);
        int i;
        for(i = 1;i < p->nombreTroudever;i++)
        {
            newtab[i] = p->troudever[i-1];
        }



        free(p->troudever);
        p->troudever = newtab;
        newtab[0] = c;

    }


    p->cases[c.y][c.x] = 5;
   /* p->cases[5][5] = 5;*/

}

/**
 * @brief ajoutTeleporter ajout dun teleporter les teleporter deplace la tete du serpent sur un trou de ver
 * @param cor les coordonnees
 * @param plat le plateau
 */
void ajoutTeleporter(coord cor,plateau *plat)
{
    if(plat->cases[cor.y][cor.x] == 0)
    {

        plat->cases[cor.y][cor.x] = 4;
        creationTroudever(plat);
        plat->nombreItem = plat->nombreItem +1;

    }
}

/**
 * @brief retirerBonus permet d enlever un objet sur une case du plateau
 * @param cor la coordonnee
 * @param plat le plateau
 */
void retirerBonus(coord cor,plateau *plat)
{
    if(plat->cases[cor.y][cor.x] > 1)
    {
        plat->cases[cor.y][cor.x] = 0;
        plat->nombreItem--;
    }
}
/**
 * @brief placerFruit permet de placer un bonus sur le plateau
 * @param plat le plateau
 */
void placerFruit(plateau *plat)
{


    if(plat->nombreItem < MAX_NB_ITEM)
    {
        int r;
        int type;

        r = rand() % 100;

        if(r < CH_SPAWNFRUIT)
        {
            type = rand() % NB_TYPE_ITEM;
            coord c = avoirCoordonneesLibreHasard(*plat);

            switch (type) {
            case 1:
                ajoutPoison(c,plat);
                break;
            case 2:
                if(plat->nombreTroudever < MAX_TELEPORT)
                {
                ajoutTeleporter(c,plat);
                }
                break;
            default:
                ajoutFruit(c,plat);
                break;
            }

        }
    }

}

/**
 * @brief detectionFruit permet de detecter la presence dun bonus sur une case
 * @param c la coordonnee
 * @param plat le plateau
 * @return un bonus est present?
 */
bool detectionFruit(coord c,plateau* plat)
{
    return plat->cases[c.y][c.x] >= 2;
}
/**
 * @brief utiliserTeleporter permet au serpent dutiliser le teleporter le serpent se teleporte sur un trou de ver le teleporter et le trou ver
 * sont ensuite detruit
 * @param p le plateau
 * @param s le serpent
 * @param dSerpent le direction du serpent
 */
void utiliserTeleporter(plateau* p ,snake* s,direction dSerpent)
{
   /* coord c;
    c.x = 5;
    c.y = 5;*/
    int r;

    r = rand() % p->nombreTroudever;

    coord c = p->troudever[r];


    int i,k = 0;

    coord* newtab = malloc(sizeof(coord)*p->nombreTroudever-1);

    for(i=0;i < p->nombreTroudever;i++)
    {
        if(i != r)
        {
            newtab[k] = p->troudever[i];
            k++;
        }

    }
    p->cases[c.y][c.x] = 0;

    free(p->troudever);
    p->troudever= newtab;
    p->nombreTroudever--;
    teleport_snake(s,dSerpent,c);
}

/**
 * @brief fruit_strategie permet de gerer les differents cas de figure pour un serpent
 * lorsqu il atterit sur une case contenant un bonus
 * @param p le plateau
 * @param s le serpent
 * @param caseFruit la coordonnee de la case
 * @param dserpent la direction du serpent
 */
void fruit_strategie(plateau *p,snake *s,coord caseFruit,direction dserpent)
{
    switch (p->cases[caseFruit.y][caseFruit.x]) {
    case 2: //fruit
        retirerBonus(caseFruit,p);
        add_taille_snake(s,dserpent);

        break;
    case 3: //poison
        retirerBonus(caseFruit,p);
        remove_taille_snake(s,dserpent);
        break;
    case 4: //teleporter
        retirerBonus(caseFruit,p);
        utiliserTeleporter(p,s,dserpent);
    case 5: //Trou de vers
        movesnake(*s,dserpent);
        break;
    default:
        //NADA
        break;
    }
}
