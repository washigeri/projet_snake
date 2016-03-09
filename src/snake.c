#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"


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
    res.playType=(type*) malloc (sizeof(type));
    res.playType[0]=typesnake;
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
    snake.playType[0] = typeAI;
}








