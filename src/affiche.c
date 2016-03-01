#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"

bool cherche_snake(int i, int j, snake s){
    bool res=false;
    int k=1;
    while(k<s.taille && !res){
        if(s.pos[k].x==j && s.pos[k].y==i){
            res=true;
        }
        k++;
        }
    return res;
}

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

