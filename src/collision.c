#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include "struct.h"
#include "fruit.h"
#include "snake.h"
#include "collision.h"


#define MAX_NB_SNAKE 10



bools* init_bools_tab(int n){
    bools* res=(bools*) malloc (n*sizeof(bools));
    for(int i=0;i<n;i++){
        res[i].b=true;
    }
    return res;
}
/**
 * \brief wall_hit Permet de tester si le serpent touche un mur du plateau
 * \param p le plateau de jeu
 * \param s les differents serpents du jeu
 * \param n le nombre de serpents
 * \return la cas de collision avec un mur
 */



bools* wall_hit(plateau p, snake* s,int n){
    bools* res=init_bools_tab(MAX_NB_SNAKE);
    int taille=p.taille;
    int i;
    for(i=0;i<n;i++){
        res[i].s=s[i];
        if(!res[i].s.dead[0]){
            if (s[i].pos[0].x==0 || s[i].pos[0].x==taille-1 || s[i].pos[0].y==0 || s[i].pos[0].y==taille-1){
                res[i].b=false;
            }
        }
    }
    return res;
}
/**
 * \brief body_hit_aux Permet de tester le cas de collision entre deux serpents
 * \param s1 serpent 1
 * \param s2 serpent 2
 * \return le cas de collision
 */

bools body_hit_aux(snake s1, snake s2){
    bools res;

    int k=0;
    res.b=true;
    res.s=s1;
    if(!s1.dead[0] && !s2.dead[0]){

        if(egalite_snake(s1,s2)){
            k=1;
        }

        while(k<s2.taille && res.b){
            if(s1.pos[0].x==s2.pos[k].x && s1.pos[0].y==s2.pos[k].y){
                res.b=false;
            }
            k++;
        }

    }
    return res;
}
/**
 * \brief body_hit Permet de tester les collisions de tous les serpents entre eux
 * \param s le tableau de serpent
 * \param n le nombre de serpent
 * \return le cas de collision entre serpents
 */

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

/**
 * \brief collisions Permet de occuper de tout les sorte de collisions entre le
 * plateau et les sepents
 * \param p le plateau forme
 * \param s la liste de serpent du jeu
 * \param n le nombre de serpent
 * \return le cas de collision
 */
bools* collisions(plateau p,snake* s,int n){
    bools* res=init_bools_tab(MAX_NB_SNAKE);
    bools* wh=wall_hit(p,s,n);
    bools* bh=body_hit(s,n);
    int i;
    for(i=0;i<n;i++){
        res[i].b=(wh[i].b && bh[i].b);
        res[i].s=s[i];
    }

    free(wh);
    free(bh);

    return res;
}

/**
 * \brief estOccupe Permet de savoir si une case est occupe par un serpent ou un obstacle
 * \param c la coordonnes de la case
 * \param snakes le tableau de serpent
 * \param nombreSerpent le nombre de serpent
 * \param p le plateau
 * \return vrai si occupe
 */
bool estOccupe(coord c ,snake * snakes ,int nombreSerpent, plateau p)
{
    bool res = false;
    int i=0,j=0;

    /*Test du plateau*/
    res = (p.cases[c.x][c.y] == 1);

    /*Test des serpents*/
    for(i= 0 ; i < nombreSerpent && !res ; i++)
    {
        if(!snakes[i].dead[0])
        {
            for(j= 0; j < snakes[i].taille && !res ; j++)
            {
                res  = (snakes[i].pos[j].x==c.x && snakes[i].pos[j].y==c.y);
            }
        }
    }
    return res;
}
