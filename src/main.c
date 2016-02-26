#include "struct.h"
#include "jeu.h"
#include "snake.h"

int main(){
    snake s=init_snake(2);
    s.pos[0].x=10;s.pos[0].y=10;
    s.pos[1].x=9;s.pos[1].y=10;
    plateau p=init_plateau(20);
    affiche(p,s);
    while(!jouer(s,p)){
        affiche(p,s);
    }
    return 0;}
