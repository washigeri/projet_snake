#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "struct.h"
#include "snake.h"
#include "affiche.h"

#define MAX_NB_SNAKE 10

plateau init_plateau(int n){
    plateau res;
    res.cases=(int**)malloc(n*sizeof(int*));
    int i;
    for(i=0;i<n;i++){
        res.cases[i]=(int*)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
    	res.cases[i][0]=1;
    	res.cases[i][n-1]=1;
    	res.cases[0][i]=1;
    	res.cases[n-1][i]=1;
    }
    res.taille=n;
    return res;
}

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

bools* init_bools_tab(int n){
    bools* res=(bools*) malloc (n*sizeof(bools));
    for(int i=0;i<n;i++){
    	res[i].b=true;
    }
    return res;
}

bools* wall_hit(plateau p, snake* s,int n){
    bools* res=init_bools_tab(MAX_NB_SNAKE);
    int taille=p.taille;
    int i;
    for(i=0;i<n;i++){
    	res[i].s=s[i];
    	if (s[i].pos[0].x==0 || s[i].pos[0].x==taille-1 || s[i].pos[0].y==0 || s[i].pos[0].y==taille-1){
    	    res[i].b=false;
    	}
    }
    return res;
}
    

bools body_hit_aux(snake s1, snake s2){
  bools res;
  res.b=true;
  res.s=s1;
  if(!egalite_snake(s1,s2)){
      int k=0;
      while(k<s2.taille && res.b){
          if(s1.pos[0].x==s2.pos[k].x && s1.pos[0].y==s2.pos[k].y){
              res.b=false;
          }
          k++;
      }
  }
  return res;
}

bools* body_hit(snake* s,int n){
    bools* res=init_bools_tab(MAX_NB_SNAKE);
    int i,j;
    bools test;
    for(i=0;i<n;i++){
    	res[i].s=s[i];
    	for(j=0;j<n;j++){
    	    test=body_hit_aux(s[i],s[j]);
    	    if(!test.b){
    	    	res[i].b=false;
    	    	j=n;
    	    }
    	}
    }
    return res;
}

bools* collisions(plateau p,snake* s,int n){
    bools* res=init_bools_tab(MAX_NB_SNAKE);
    bools* wh=wall_hit(p,s,n);
    bools* bh=body_hit(s,n);
    int i;
    for(i=0;i<n;i++){
    	res[i].b=(wh[i].b && bh[i].b);
    	res[i].s=s[i];
    }
    return res;
}


bool win(bools* bs,snake* s,int n){
    bool res=true;
    if(!bs[0].b){
        printf("PJSalt G A M E O V E R  PJSalt\n\n");
        res=false;
    }
    else {
        int i;
        for(i=1;i<n;i++){
            if(!bs[i].b){
                printf("V I C T O I R E, le bot %d est crevé EleGiggle\n\n",i);
                i=n;
                res=false;
    	    }   
        }  
    }
    return res;
}

int kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf=tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

void depart(snake* s,int n, plateau p){
    char dir,dir2;
    bool debut=false;
    while(!debut){
    	if(kbhit()){
    	    dir=getchar();
    	    if(dir=='z' || dir=='q' || dir=='s' || dir=='d'){
    	        dir2=choix_strategie(s[1],s,n,p,0);
    	        debut=true;
    	    }
    	}
    }
    movesnake(s[0],dir);
    movesnake(s[1],dir2);
}
    

bools* jouer(snake* s,int n,plateau p){
    char dir=s[0].dir[0];
    if(kbhit()){
    	dir=getchar();
    }
    if(dir=='z' || dir=='q' || dir=='s' || dir=='d'){
        direction dir2=choix_strategie(s[1],s,n,p,0);
        movesnake(s[0],dir);
        affiche(p,s,n);
        movesnake(s[1],dir2);
        affiche(p,s,n);
    }
    else {
    	movesnake(s[0],s[0].dir[0]);
    	affiche(p,s,n);
    	movesnake(s[1],choix_strategie(s[1],s,n,p,0));
    	affiche(p,s,n);
    }
    bools* res=collisions(p,s,n);
    usleep(100000);
    return res;
}

