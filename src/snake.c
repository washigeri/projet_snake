#include <stdio.h>
#include <stdlib.h>
#include "struct.h"


/**
 * @brief init_snake Permet la creation dun serpent dune taille definie
 * @param len taille du serpent
 * @return le serpent cree
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
    res.playType=(type*) malloc (sizeof(type));
    res.playType[0]=typesnake;
    return res;
}


/**
 * @brief change_IA Permet le changement de l'intellgence artificielle d un serpent
 * @param snake
 * @param typeAI
 */
 
void change_IA(snake snake, type typeAI )
{
    snake.playType[0] = typeAI;
}

void add_taille_snake(snake snak){
    int i;
    snak.taille=snak.taille+1;
    for(i=1;i<snak.taille;i=i+1){
        snak[i].pos=snak[i-1].pos;
    }
    snak[0].pos.x=convertDirectionToCoord(*dir).x+snak[0].pos.x;
    snak[0].pos.y=convertDirectionToCoord(*dir).x+snak[0].pos.y;
}






