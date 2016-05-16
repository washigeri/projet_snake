#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "struct.h"
#include "snake.h"
#include "fruit.h"

#define CH_SPAWNFRUIT 50 //sur 100

#define MAX_NB_ITEM 100
#define MAX_TELEPORT 3

#define NB_TYPE_ITEM 3

#define MARGE 5
/** Gestion des Bonus
 * */


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



void ajoutFruit(coord cor,plateau* plat)
{
    if(plat->cases[cor.y][cor.x] == 0)
    {
        plat->cases[cor.y][cor.x] = 2;
        plat->nombreItem++;
    }

}

void ajoutPoison(coord cor,plateau* plat)
{
    if(plat->cases[cor.y][cor.x] == 0)
    {
        plat->cases[cor.y][cor.x] = 3;
        plat->nombreItem++;
    }

}


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

void ajoutTeleporter(coord cor,plateau *plat)
{
    if(plat->cases[cor.y][cor.x] == 0)
    {

        plat->cases[cor.y][cor.x] = 4;
        creationTroudever(plat);
        plat->nombreItem = plat->nombreItem +1;

    }
}


void retirerBonus(coord cor,plateau *plat)
{
    if(plat->cases[cor.y][cor.x] > 1)
    {
        plat->cases[cor.y][cor.x] = 0;
        plat->nombreItem--;
    }
}
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


bool detectionFruit(coord c,plateau* plat)
{
    return plat->cases[c.y][c.x] >= 2;
}

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
