#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "jeu.h"

/**
 * @brief init_snake Permet la creation dun serpent dune taille definie
 * @param len taille du serpent
 * @return le serpent créé
 */

snake init_snake(int len,type typesnake){
    snake res;
    res.pos=(coord*)malloc(len*sizeof(coord));
    int i;
    for(i=0;i<len;i++){
        res.pos[i].x=0;
        res.pos[i].y=0;
    }
    res.taille=len;
    res.dir=(direction *) malloc (sizeof(direction));
    res.dir[0]=right;
    res.playType=typesnake;
    return res;
}

/**
 * @brief test si 2 serpents sont égaux
 * @param snake
 * @param snake
 */

bool egalite_snake(snake s1, snake s2){
    bool res=false;
    if(s1.taille==s2.taille){
        int i=0;
        while(i<s1.taille && s1.pos[i].x==s2.pos[i].x && s1.pos[i].y==s2.pos[i].y){
            i++;
        }
        if(i==s1.taille){
            res=true;
        }
    }
    return res;
}


/**
 * @brief change_IA Permet le changement de l'intellgence artificielle d un serpent
 * @param snake
 * @param typeAI
 */

void change_IA(snake snake, type typeAI )
{
    snake.playType = typeAI;
}


direction choix_strategie(snake cible,snake* snakes,int nombreSerpent, plateau p,direction toucheJoueur){

    switch(cible.playType)
    {
    case 0 :
        return toucheJoueur;
        break;
    case 1 :
        return idle(cible,snakes,nombreSerpent,p);
        break;
    default:
        return toucheJoueur;

    }
}


bool estOccupe(coord c ,snake * snakes ,int nombreSerpent, plateau p)
{
    bool res = false;
    int i,j;

    /*Test du plateau*/
    res = (p.cases[c.x][c.y] == 1);

    /*Test des serpents*/
    for(i= 0 ; i < p.taille && !res ; i++)
    {
        for(j= 0; j < nombreSerpent && !res ; j++)
        {
            res  = (snakes[i].pos[j]);

        }
    }


    return res;

}

bool estInverse(direction dir1,direction dir2)
{
    if(dir1 == left )
    {
        return (dir2 == right);
    }
    else if (dir1 == right)
    {
        return (dir2 == left);
    }
    else if (dir1 == up)
    {
        return (dir2 == down);
    }
    else
    {
        return (dir2 == up);
    }
}

direction joueur(snake cible,direction toucheJoueur)
{
    if(estInverse(*(cible.dir),toucheJoueur))
    {
        return *(cible.dir);
    }
    else
    {
        return toucheJoueur;
    }

}

coord convertDirectionToCoord(direction dir)
{
    coord res;

    if(dir == left)
    {
        res.x =-1;
        res.y = 0;
    }
    else if(dir == right)
    {
        res.x = 1;
        res.y = 0;
    }
    else if(dir == up)
    {
        res.x = 0;
        res.y = -1;
    }
    else
    {
        res.x = 0;
        res.y = 1;
    }

    return res;

}

direction tournerAntiHoraire(direction dir)
{

    if(dir == left)
    {
        return down;
    }
    else if(dir == right)
    {

        return up;
    }
    else if(dir == up)
    {
        return left;
    }

    return right;


}

direction idle(snake cible, snake* snakes,int nombreSerpent, plateau p){


    direction res = (*(cible.dir));

    direction old = res;

    int testmax = 0;
    coord dirSouhaite,dirFutur;


    //On test si le serpent peut aller autre part (si ou bout de 3 test le test echoue le serpent se suicide
    while(testmax < 4 && estOccupe(dirSouhaite,snakes,nombreSerpent,p))
    {
        res =tournerAntiHoraire(res);

        //Test si
        if(estInverse(res,old))
        {

            dirFutur = convertDirectionToCoord(res);
            dirSouhaite.x = cible.pos->x + dirFutur.x;
            dirSouhaite.y = cible.pos->y + dirFutur.y;
        }
        testmax++;

    }


    return res;

}


