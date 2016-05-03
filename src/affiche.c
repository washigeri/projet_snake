/**
 * \file affiche.c
 * \brief Ce fichier source contient les fonctions gerant l'affichage du jeu
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "struct.h"
#include "snake.h"

/**
 * \brief check Fonction cherchant si un tableau de booléen contient une valeur true
 * \param un tableau de booléens
 * \param n la taille du tableau
 * \return true si le tableau contient au moins une valeur true, false sinon
 */

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

    free(b);

    return res;
}
/**
 * \brief cherche_snake fonction dont l'objectif est de déterminer si le corps d'un serpent (et pas sa tête) se situe sur la case de coordonnées i,j
 * \param i un entier correspondant a l'absisse d'une coordonnée
 * \param j un entier correspondant a l'ordonnée d'une coordonnée
 * \param s les serpents
 * \param n le nombre de serpents
 * \return Un tableau de booléens de taille n
 */
bool* cherche_snake(int i, int j, snake* s, int n){
    bool* res=(bool*) calloc (n,sizeof(bool));
    int k,l;
    for(l=0;l<n;l++){
    	k=1;
        while(k<s[l].taille && !res[l]){
            if(!(s[l].dead[0]) && s[l].pos[k].x==j && s[l].pos[k].y==i){
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

/**
 * \brief cherche_tete fonction dont l'objectif est de déterminer si la tête d'un serpent se situe sur la case de coordonnées i,j
 * \param i un entier correspondant a l'absisse d'une coordonnée
 * \param j un entier correspondant a l'ordonnée d'une coordonnée
 * \param s les serpents
 * \param n le nombre de serpents
 * \return Un tableau de booléens de taille n
 */
bool* cherche_tete(int i,int j, snake* s, int n){
    bool* res=(bool*) calloc (n,sizeof(bool));
    int k;
    for(k=0;k<n;k++){
        if(!(s[k].dead[0]) && s[k].pos[0].x==j && s[k].pos[0].y==i){
            res[k]=true;
        }
    }
    return res;
}

/**
 * \brief affiche Permet d'afficher le plateau et les serpents à un instant donné
 * \param s les serpents
 * \param n le nombre de serpents
 * \return void
 */
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



void jeu_sdl(SDL_Surface* screen, snake* s, int nbs, plateau p){
    SDL_Surface* wall=NULL;
    SDL_Surface* snake=NULL;
    int taille_cases_px=screen->h/p.taille;
    wall=SDL_CreateRGBSurface(0,taille_cases_px,taille_cases_px,32,0,0,0,0);
    snake=SDL_CreateRGBSurface(0,taille_cases_px,taille_cases_px,32,0,0,0,0);
    SDL_FillRect(wall,NULL,SDL_MapRGB(screen->format,255,140,0));
    SDL_FillRect(snake,NULL,SDL_MapRGB(screen->format,205,0,205));
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,140,140,140));
    SDL_Rect position_mur;
    position_mur.x=0;
    position_mur.y=0;
    int i,j;
    for(i=0;i<p.taille;i++){
        position_mur.x=i*taille_cases_px;
        for(j=0;j<p.taille;j++){
            if(i==0 || j==0 || i==p.taille-1 || j==p.taille-1){
                position_mur.y=j*taille_cases_px;
                SDL_BlitSurface(wall,NULL,screen,&position_mur);
                }
            }

        }
    SDL_FreeSurface(wall);
    SDL_Rect position_snake;
    position_snake.x=0;
    position_snake.y=0;
    int k;
    for(k=0;k<nbs;k++){
        for(i=0;i<s[k].taille;i++){
            position_snake.x=s[k].pos[i].x*taille_cases_px;
            position_snake.y=s[k].pos[i].y*taille_cases_px;
            SDL_BlitSurface(snake,NULL,screen,&position_snake);

            }
        }
    SDL_FreeSurface(snake);

    }





