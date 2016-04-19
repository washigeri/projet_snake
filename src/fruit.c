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

#define CH_SPAWNFRUIT 50 //sur 100


/** Gestion des Bonus
 * */
void ajoutFruit(coord cor,plateau plat)
{
    if(plat[cor.x][cor.y] == 0)
    {
        plat.cases[cor.x][cor.y] = 2;
    }

}

void retirerFruit(coord cor,plateau plat)
{
    if(plat[cor.x][cor.y] > 1)
    {
        plat[cor.x][cor.y] = 0;
    }
}
void placerFruit(plateau plat)
{
    int rand;
    int x,y;

    rand = rand() % 100;

    if(rand < CH_SPAWNFRUIT)
    {

        x = rand() % plat.taille;
        y = rand() % plat.taille;

        coord c;
        c.x = x;
        c.y = y;

        ajoutFruit(c,plat);
    }

}

void detectionFruit(coord c,plateau plat)
{
    return plat[c.x][c.y] == 2;
}
