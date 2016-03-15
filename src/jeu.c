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
    	res.cases[0][n-1]=1;
    }
    res.taille=n;
    return res;
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
    

bools body_hit_aux1(snake s1, snake s2){
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

bools** body_hit_aux2(snake *s, int n){
    bools** res=(bools**)malloc((MAX_NB_SNAKE)*sizeof(bools*));
    bools* ligne=init_bools_tab(MAX_NB_SNAKE);
    int i,j;
    for(i=0;i<n;i++){
    	res[i]=ligne;
    }
    for(i=0;i<n;i++){
    	for(j=0;j<n;j++){
    	    res[i][j]=body_hit_aux1(s[i],s[j]);
    	}
    }
    return res;
}

bools* body_hit(snake* s,int n){	
    bools* res=init_bools_tab(MAX_NB_SNAKE);
    bools** all_hits=body_hit_aux2(s,n);
    int i,j;
    for(i=0;i<n;i++){
    	j=0;
    	while(j<n && res[i].b){	
    	    if(all_hits[i][j].b){
    	    	j++;
    	    }
    	    else {
    	        res[i].b=false;
    	    }
    	}
    	res[i].s=s[i];
    	if(j!=n){
    	    res[i].b=false;
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


void win(bools* bs,snake* s,int n){
    if(!bs[0].b){
        system("clear");
        printf("PJSalt G A M E O V E R  PJSalt\n\n");
    }
    else {
        int i;
        for(i=1;i<n;i++){
            if(!bs[i].b){
                printf("V I C T O I R E, le bot %d est crevé EleGiggle\n\n",i-1);
    	    }   
        }  
    }
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

bools* jouer(snake* s,int n,plateau p){
    char dir=s[1].dir[0];
    if(kbhit()){
    	dir=getchar();
    }
    movesnake(s[0],dir);
    movesnake(s[1],dir);
    bools* res=collisions(p,s,n);
    win(res,s,n);
    usleep(200000);
    return res;
}

