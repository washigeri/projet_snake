#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "struct.h"
#include "snake.h"

bool check(bool* b, int n){
    bool res=false;
    int i=0;
    while(i<n && !b[i]){
        i++;
    }
    if(i<n){
    	res=true;
    }
    else if(b[n-1]){
    	res=true;
    }
    return res;
}

bool* cherche_snake(int i, int j, snake* s, int n){
    bool* res=(bool*) malloc (n*sizeof(bool));
    int k,l;
    for(l=0;l<n;l++){
    	k=1;
        while(k<s[l].taille && !res[l]){
            if(s[l].pos[k].x==j && s[l].pos[k].y==i){
                res[l]=true;
            }
            else {
            	res[l]=false;
            }
            k++;
        }
    }    
    return res;
}

bool* cherche_tete(int i,int j, snake* s, int n){
    bool* res=(bool*) malloc (n*sizeof(bool));
    int k;
    for(k=0;k<n;k++){
        if(s[k].pos[0].x==j && s[k].pos[0].y==i){
            res[k]=true;
        }
        else {
            res[k]=false;
        }
    }
    return res;
}

void affiche(plateau p, snake* s,int n){
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
            else if(check(cherche_tete(i,j,s,n),n)){
                printf(":)");
            }
            else if(check(cherche_snake(i,j,s,n),n)){
                printf("==");
            }
            else{
                printf("  ");
            }
        }
        printf("\n");
    }
}





