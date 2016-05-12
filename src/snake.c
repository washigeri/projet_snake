/**
 * \file snake.c
 * \brief Ce source contient l'implémentation des fonctions permettant la manipulation des serpents
*/

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
#include "snake.h"
#include "collision.h"

/* AntiBlocage, Plus le coefficient est eleve moins le serpents aura tendance a s'enrouler
 *autour de lui-meme*/
#define COEFF_TARGETSNAKE 1
/* Aggresivite, Plus le coefficient est haut plus le serpent evitera ses congeneres*/
#define COEFF_OTHERSNAKE 3
/* Liberte, plus le coefficient est eleve, plus le serpent voudra eloigner des murs du plateau*/
#define COEFF_PLATEAU 5
/* Prevoyance ,plus le coefficient est eleve plus le serpent se mefira de la tete des autres serpents*/
#define COEFF_HEAD 9



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



void add_taille_snake(snake *snak,direction dir){
    int i;
    snak->taille++;
/*	snak->pos=(coord*)realloc(snak->pos,(snak->taille));
//On décale les pos

    for(i=1;i<snak->taille;i++){
       	snak->pos[i]=snak->pos[i-1];
    }
*/

    coord* new_pos=malloc((snak->taille)*sizeof(coord));
    for(i=1;i<snak->taille;i++){
        new_pos[i].x=snak->pos[i-1].x;
        new_pos[i].y=snak->pos[i-1].y;

    }

    new_pos[0].x= convertDirectionToCoord(dir).x + snak->pos[0].x;
    new_pos[0].y= convertDirectionToCoord(dir).y + snak->pos[0].y;

    free(snak->pos);
    snak->pos=new_pos;

	//return snak.taille;
}
