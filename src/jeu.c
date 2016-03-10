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

bools wall_hit(plateau p, snake* s,int n){
    bools res;
    res.b=false;
    res.s=s[0];
    int taille=p.taille;
    int i;
    for(i=0;i<n;i++){
    	if (s[i].pos[0].x==0 || s[i].pos[0].x==taille-1 || s[i].pos[0].y==0 || s[i].pos[0].y==taille-1){
    	    res.b=true;
    	    res.s=s[i];
    	}
    }
    return res;
}

bools head_s_hit(snake s1, snake s2){
  bools res;
  res.b=false;
  res.s=s1;
  int k=0;
  while(k<s1.taille && !res.b){
    if(s2.pos[0].x==s1.pos[k].x && s2.pos[0].y==s1.pos[k].y){
      res.b=true;
      res.s=s2;
    }
    k++;
  }
  k=0;
  while(k<s2.taille && !res.b){
    if(s1.pos[0].x==s2.pos[k].x && s1.pos[0].y==s2.pos[k].y){
      res.b=true;
      res.s=s1;
    }
    k++;
  }
  return res;
}

bools body_hit(snake* s, int n){
  bools res;
  res.b=false;
  int i=0;
  int j;
  while(i<n && !res.b){
    j=i+1;
    while(j<n && !res.b){
      res=head_s_hit(s[i],s[j]);
      j++;
    }
    i++;
  }
  return res;
}

bools collisions(plateau p,snake* s,int n){
  bools res;
  bools wh=wall_hit(p,s,n);
  bools bh=body_hit(s,n);
  res.b = (wh.b || bh.b);
  if(res.b){
      if((wh.b && egalite_snake(wh.s,s[0])) || (bh.b && egalite_snake(bh.s,s[0]))){
          res.s=s[0];
      }
      else if(wh.b){
      	  res.s=wh.s;
      }
      else {
          res.s=bh.s;
      }
  }
  return res;
}

void win(bools bs,snake s){
    if(bs.b){
        system("clear");
        if(egalite_snake(bs.s,s)){
            printf("PJSalt G A M E O V E R  PJSalt\n\n");
        }
        else {
            printf("V I C T O I R E\n\n");
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

bools jouer(snake* s,int n,plateau p){
    char dir=s[0].dir[0];
    if(kbhit()){
    	dir=getchar();
    }
    movesnake(s[0],dir);
    //movesnake(s[1],dir);
    bools res=collisions(p,s,n);
    win(res,s[0]);
    usleep(100000);
    return res;
}

