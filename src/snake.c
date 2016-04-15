
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#include "struct.h"
#include "jeu.h"
#include "snake.h"
/* AntiBlocage, Plus le coeff est eleve moins le serpents aura tendance a l'enrouler
 *autour de lui-meme*/
#define COEFF_TARGETSNAKE 1
/* Aggresivite, Plus le coeff est haut plus le serpent evitera ses congeneres*/
#define COEFF_OTHERSNAKE 3
/* Liberte, plus le coefficient est eleve, plus le serpent voudra eloigner des murs du plateau*/
#define COEFF_PLATEAU 10
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
void change_IA(snake snake, type typeAI)

{
    snake.playType = typeAI;
}






bool estOccupe(coord c ,snake * snakes ,int nombreSerpent, plateau p)

{
    bool res = false;
    int i,j;

    /*Test du plateau*/
    res = (p.cases[c.x][c.y] == 1);

    printf("**Test plateau x= %d y= %d == %d  \n",c.x,c.y,res);


    /*Test des serpents*/
    for(i= 0 ; i < nombreSerpent && !res ; i++)
    {
        for(j= 0; j < snakes[i].taille && !res ; j++)
        {
            res  = (snakes[i].pos[j].x==c.x && snakes[i].pos[j].y==c.y);

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

direction joueur_strat(snake cible,direction toucheJoueur)
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

direction idle_strat(snake cible, snake* snakes,int nombreSerpent, plateau p){


    direction res = (*(cible.dir));

    direction old =res;

    int testmax = 0;
    coord dirSouhaite,dirFutur;

    dirFutur = convertDirectionToCoord(res);

    dirSouhaite.x = cible.pos->x + dirFutur.x;
    dirSouhaite.y = cible.pos->y + dirFutur.y;

    //On test si le serpent peut aller autre part (si ou bout de 3 test le test echoue le serpent se suicide)
    while(testmax < 5 && estOccupe(dirSouhaite,snakes,nombreSerpent,p))
    {

        /*TODO:Et si le serpent a une taille de 1 ?*/
        res =tournerAntiHoraire(res);
        //Test si
        if(!estInverse(res,old))
        {
            dirFutur = convertDirectionToCoord(res);
            dirSouhaite.x = cible.pos->x + dirFutur.x;
            dirSouhaite.y = cible.pos->y + dirFutur.y;
        }
        testmax++;
    }

    return res;

}

int calculDistanceTaxicab(coord cor1,coord cor2)
{

    int res = 0;

    /*x*/
    res = abs((cor1.x - cor2.x));
    /*y*/
    res += abs((cor1.y -cor2.y));


    return res;

}

int calculPoidsTableau(coord cor,plateau p)
{
    int res;

    coord cort;
    cort.x = p.taille/2;
    cort.y = p.taille/2;

    res = p.taille - calculDistanceTaxicab(cor,cort);

    return res * COEFF_PLATEAU;
}

int calculPoidsSerpent(coord pos,snake cible,snake * snakes,int nombreSerpent,plateau p)
{
    int res = 0;

    int i,j;

    for(i = 0 ; i < nombreSerpent;i++)
    {
        if(egalite_snake(snakes[i],cible))
        {
            for(j = 0; j < snakes[i].taille ; j++)
            {

                res += calculDistanceTaxicab(snakes[i].pos[j],pos) * COEFF_TARGETSNAKE;
            }

        }
        else
        {
            for(j = 0; j < snakes[i].taille ; j++)
            {


                res += calculDistanceTaxicab(snakes[i].pos[j],pos) * COEFF_OTHERSNAKE;
            }

        }

    }

    return res;

}

direction defensiv_strat(snake cible,snake* snakes,int nombreSerpent,plateau p)
{
    int poids = -1;
    direction actuel = *cible.dir;
    direction res = *cible.dir;
    coord coor;

    int i;
    for(i = 0; i < 4 ; i++)
    {

        coor.x = convertDirectionToCoord(actuel).x + cible.pos->x;
        coor.y = convertDirectionToCoord(actuel).y + cible.pos->y;


        if(!estOccupe(coor,snakes,nombreSerpent,p))
        {
            int poidscurrent = 0;
            poidscurrent += calculPoidsTableau(coor,p);
            poidscurrent += calculPoidsSerpent(coor,cible,snakes,nombreSerpent,p);

            if(poids <= poidscurrent)
            {
              poids = poidscurrent;
              res = actuel;

            }

        }

        actuel = tournerAntiHoraire(actuel);
    }

    return res;




}


direction choix_strategie(snake cible,snake* snakes,int nombreSerpent, plateau p,direction toucheJoueur){


    switch(cible.playType)
    {

    case joueur :
        return toucheJoueur;
        break;
    case idle :
        return idle_strat(cible,snakes,nombreSerpent,p);
        break;
    case defensif :
        return defensiv_strat(cible,snakes,nombreSerpent,p);
        break;
    case offensif :
        return 0;
        break;
    default :
        return toucheJoueur;
        break;
    }
}
