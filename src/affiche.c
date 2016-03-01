#include <stdio.h>
#include "struct.h"



void affiche(plateau p, snake s){
    system("clear");
    int i,j;
    for(i=0;i<p.taille;i++){
        for(j=0;j<p.taille;j++){
            if((i==0 && j==0)||(i==p.taille-1 && j==0)||(i==0 && j==p.taille-1)||(i==p.taille-1 && j==p.taille-1)){
                printf("+");
            }
            else if(j==0 || j==p.taille-1){
                printf("|");
            }
            else if (i==0 || i==p.taille-1){
                printf("--");
            }
            else if(s.pos[0].x==j && s.pos[0].y==i){
                printf(":)");
            }
            else if(cherche_snake(i,j,s)){
                printf("==");
            }
            else{
                printf("  ");
            }
        }
        printf("\n");
    }
}