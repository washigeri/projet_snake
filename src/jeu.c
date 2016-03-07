#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "struct.h"



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



bool wall_hit(plateau p, snake* s,int n){
    bool res=false;
    int taille=p.taille;
    int i;
    for(i=0;i<n;i++){
    	if (s[i].pos[0].x==0 || s[i].pos[0].x==taille-1 || s[i].pos[0].y==0 || s[i].pos[0].y==taille-1){
    	    res=true;
    	}
    }
    return res;
}	
bool head_s_hit(snake s1, snake s2){
  bool res=false;
  int k=0;
  while(k<s1.taille && !res){
    if(s2.pos[0].x==s1.pos[k].x && s2.pos[0].y==s1.pos[k].y){
      res=true;
    }
    k++;
  }
  k=0;
  while(k<s2.taille && !res){
    if(s1.pos[0].x==s2.pos[k].x && s1.pos[0].y==s2.pos[k].y){
      res=true;
    }
    k++;
  }
  return res;
}




bool body_hit(snake* s, int n){
  bool res=false;
  int i,j;
  for(i=0;i<n;i++){
    for(j=i+1;j<n;j++){
      res=head_s_hit(s[i],s[j]);
    }

  }
  return res;
}


int kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
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

bool jouer(snake* s,int n,plateau p){
    char dir=s[0].dir[0];
    if(kbhit()){
    	dir=getchar();
    }
    movesnake(s[0],dir);
    movesnake(s[1],dir);
    usleep(100000);
    return (wall_hit(p,s,n) || body_hit(s,n));
}

