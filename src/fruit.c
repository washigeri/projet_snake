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
#include "fruit.h"

#define CH_SPAWNFRUIT 50 //sur 100


/** Gestion des Bonus
 * */
void ajoutFruit(coord cor,plateau plat)
{
    if(plat.cases[cor.y][cor.x] == 0)
    {
        plat.cases[cor.y][cor.x] = 2;
    }

}

void retirerFruit(coord cor,plateau plat)
{
    if(plat.cases[cor.y][cor.x] > 1)
    {
        plat.cases[cor.y][cor.x] = 0;
    }
}
void placerFruit(plateau plat)
{
    int r;
    int x,y;

    r = rand() % 100;

    if(r < CH_SPAWNFRUIT)
    {

        x = rand() % plat.taille;
        y = rand() % plat.taille;

        coord c;
        c.x = x;
        c.y = y;

        ajoutFruit(c,plat);
    }

}

int detectionFruit(coord c,plateau plat)
{
    return plat.cases[c.y][c.x] == 2;
}
