/**
 * \file snake.c
 * \brief Ce source contient l'implémentation des fonctions permettant la manipulation des serpents
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "struct.h"
#include "snake.h"
#include "collision.h"


#define TAILLE_MIN 2
#define TAILLE_MAX 32


/**
 * \brief init_snake Permet la creation dun serpent dune taille definie
 * \param len taille du serpent
 * \return le serpent cree
 */
snake init_snake(int len,type typesnake){
    snake res;
    res.pos=(coord*)calloc(len,sizeof(coord));
    int i;
    for(i=0;i<len;i++){
        res.pos[i].x=0;
        res.pos[i].y=0;
    }
    res.taille=len;
    res.dir=(direction *) malloc (sizeof(direction));
    res.dir[0]=right;
    res.playType=typesnake;
    res.dead=(bool*) malloc (sizeof(bool));
    res.dead[0]=false;
    res.score=(int*)calloc(1,sizeof(int));
    res.score[0]=0;
    return res;
}

/**
 * \brief kill_snake change la valeur du booleen dead a false
 * \param snakeAeffacer serpent a tuer
 */

void kill_snake(snake s){
    s.dead[0]=true;
}

/**
 * \brief delete_snake permet de detruire un snake
 * \param snakeAeffacer serpent a detruire
 */

void delete_snake(snake* snakeAeffacer){

    free(snakeAeffacer->dir);
    free(snakeAeffacer->pos);
    free(snakeAeffacer->dead);
    free(snakeAeffacer->score);

}

/**
 * \brief test si 2 serpents sont égaux
 * \param snake serpent 1
 * \param snake serpent 2
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

 * \brief change_IA Permet le changement de l'intelligence artificielle d un serpent
 * \param snake le serpent
 * \param typeAI le nouveau type dAI
 */
void change_IA(snake snake, type typeAI)

{
    snake.playType = typeAI;
}






/**
 * \brief estInverse Permet de savoir si deux coordonnees sont inversees utile pour savoir si le
 * serpent ne fais pas marche arriere
 * \param dir1
 * \param dir2
 * \return vrai si lezs cordonnees sont inversees
 */
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





/**
 * \brief convertDirectionToCoord Permet de convertir une direction en coordonnees
 *Exemple "haut" devient "0,-1"
 * \param dir la direction a convertir
 * \return la coordonnee
 */
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

/**
 * \brief movesnake Procedure de mise à jour et de deplacement du serpent dans
 * une direction donne
 * \param s le serpent a deplacer
 * \param dir la direction souhaitee
 */
void movesnake(snake s,direction dir){
    if(!estInverse(s.dir[0],dir)){
        int i;
        switch (dir){
        case right:
            for(i=s.taille-1;i>0;i--){
                s.pos[i].x=s.pos[i-1].x;
                s.pos[i].y=s.pos[i-1].y;
            }
            s.pos[0].x++;
            s.dir[0]=dir;
            break;
        case left:
            for(i=s.taille-1;i>0;i--){
                s.pos[i].x=s.pos[i-1].x;
                s.pos[i].y=s.pos[i-1].y;
            }
            s.pos[0].x--;
            s.dir[0]=dir;
            break;
        case up:
            for(i=s.taille-1;i>0;i--){
                s.pos[i].x=s.pos[i-1].x;
                s.pos[i].y=s.pos[i-1].y;
            }
            s.pos[0].y--;
            s.dir[0]=dir;
            break;
        case down:
            for(i=s.taille-1;i>0;i--){
                s.pos[i].x=s.pos[i-1].x;
                s.pos[i].y=s.pos[i-1].y;
            }
            s.pos[0].y++;
            s.dir[0]=dir;
            break;
        }
    }
    else {
        movesnake(s,s.dir[0]);
    }
}


/**
 * @brief add_taille_snake permet d augmenter la taille du serpent pendant son movement
 * @param snak le serpent
 * @param dir la direction
 */
void add_taille_snake(snake *snak,direction dir){
    int i;


    if(snak->taille < TAILLE_MAX)
    {
    snak->taille++;
    }

    coord* new_pos=malloc((snak->taille)*sizeof(coord));
    for(i=1;i<snak->taille;i++){
        new_pos[i].x=snak->pos[i-1].x;
        new_pos[i].y=snak->pos[i-1].y;

    }

    new_pos[0].x= convertDirectionToCoord(dir).x + snak->pos[0].x;
    new_pos[0].y= convertDirectionToCoord(dir).y + snak->pos[0].y;

    free(snak->pos);
    snak->dir[0]=dir;
    snak->pos=new_pos;
}
/**
 * @brief remove_taille_snake permet de reduire la taille du serpent pendant son movement
 * @param snak le serpent
 * @param dir la direction
 */
void remove_taille_snake(snake *snak,direction dir){


    int i;
    if(snak->taille > TAILLE_MIN)
    {
        snak->taille--;

    }

    coord* new_pos=malloc((snak->taille)*sizeof(coord));
    for(i=1;i<snak->taille;i++){
        new_pos[i].x=snak->pos[i-1].x;
        new_pos[i].y=snak->pos[i-1].y;

    }

    new_pos[0].x= convertDirectionToCoord(dir).x + snak->pos[0].x;
    new_pos[0].y= convertDirectionToCoord(dir).y + snak->pos[0].y;

    free(snak->pos);
    snak->dir[0]=dir;
    snak->pos=new_pos;
}
/**
 * @brief teleport_snake permet de teleporter la tete du  serpent sur une case donne
 * @param snak le serpent
 * @param dir la direction
 * @param cor la coordonnes ou mettre la tete du serpent
 */
void teleport_snake(snake *snak,direction dir,coord cor)
{
    snak->pos[0].x = cor.x;
    snak->pos[0].y = cor.y;


    snak->dir[0]=dir;
}



