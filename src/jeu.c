#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "struct.h"
#include "snake.h"



plateau init_plateau(int n){
    plateau res;
    res.cases=(int**)malloc(n*sizeof(int*));
    int i;
    for(i=0;i<n;i++){
            res.cases[i]=(int*)malloc(n*sizeof(int));
    }
    res.taille=n;
    return res;
}

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

void movesnake(snake s,direction dir){
    if((int)(abs(s.dir[0]-dir))!=7 && (int)(abs(s.dir[0]-dir))!=13){
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
}



bool wall_hit(plateau p, snake s){
    bool res=false;
    int taille=p.taille;
    if (s.pos[0].x==0 || s.pos[0].x==taille-1 || s.pos[0].y==0 || s.pos[0].y==taille-1)  res=true;

    return res;
}


bool jouer(snake s,plateau p){
    direction dir;
    scanf("%c",&dir);
    movesnake(&s,dir);
    printf("%c",dir);
    return wall_hit(p,s);
}

