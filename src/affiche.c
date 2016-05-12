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
#include <SDL/SDL_ttf.h>
#include "struct.h"
#include "snake.h"

#define NB_MAX_SERPENT 8

int tab_couleur[NB_MAX_SERPENT][3];

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

void init_tab_couleur(){
    FILE* fichier=NULL;
    fichier=fopen("others/snakes_color.data","r");
    if(fichier==NULL){
        exit(EXIT_FAILURE);
        }
    char* line_color=NULL;
    size_t n=0;
    char buffer[3];
    for(int j=0;j<NB_MAX_SERPENT;j++){
        getline(&line_color,&n,fichier);
        for(int k=0;k<strlen(line_color);k+=4){
            buffer[0]=line_color[k];
            buffer[1]=line_color[k+1];
            buffer[2]=line_color[k+2];
            tab_couleur[j][k/4]=atoi(buffer);
            }
        }
    free(line_color);
    }


void affiche_sdl(SDL_Surface* screen, snake* s, int nbs, plateau p,int temps_debut){
    int taille_cases_px=screen->h/p.taille;
    SDL_Surface* wall=NULL;
    SDL_Surface* snake=NULL;
    SDL_Surface* score=NULL;
    SDL_Rect position_score_board;
    SDL_Surface* score_board=NULL;
    TTF_Font* police=TTF_OpenFont("others/m01/m01.TTF",taille_cases_px);
    position_score_board.y=0;position_score_board.x=taille_cases_px*(p.taille);
    char score_ch[14]; SDL_Color color_white={255,255,255};
    sprintf(score_ch,"SCORE: %06d",(SDL_GetTicks()-temps_debut)/10);
    score=TTF_RenderText_Solid(police,score_ch,color_white);


    //wall=SDL_CreateRGBSurface(0,taille_cases_px,taille_cases_px,32,0,0,0,0);
    wall=IMG_Load("others/sprites/sprite_bricks_tutorial_1.png");
    //snake=SDL_CreateRGBSurface(0,taille_cases_px,taille_cases_px,32,0,0,0,0);
    snake=IMG_Load("others/sprites/snake_body_bg_mockup.png");
    score_board=SDL_CreateRGBSurface(0,(screen->w)-position_score_board.x,screen->h,32,0,0,0,0);
    //SDL_FillRect(wall,NULL,SDL_MapRGB(screen->format,255,140,0));

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,140,140,140));
    SDL_FillRect(score_board,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_Rect position_mur;

    SDL_Rect position_score;
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
        //SDL_FillRect(snake,NULL,SDL_MapRGB(screen->format,tab_couleur[k][0],tab_couleur[k][1],tab_couleur[k][2]));
        for(i=0;i<s[k].taille;i++){
            position_snake.x=s[k].pos[i].x*taille_cases_px;
            position_snake.y=s[k].pos[i].y*taille_cases_px;
            SDL_BlitSurface(snake,NULL,screen,&position_snake);

            }
        }

    SDL_BlitSurface(score_board,NULL,screen,&position_score_board);
    position_score.x=position_score_board.x+taille_cases_px;
    position_score.y=taille_cases_px;
    SDL_BlitSurface(score,NULL,screen,&position_score);
    score_snakes_sdl(screen,s,nbs,p,temps_debut,taille_cases_px,position_score_board);
    SDL_FreeSurface(snake);
    SDL_FreeSurface(score);
    TTF_CloseFont(police);

    }

void score_snakes_sdl(SDL_Surface* screen, snake* s, int nb_ser, plateau p,int tps_debut, int taille_px, SDL_Rect position_scoreboard){
    TTF_Font* police_score_snake=NULL;
    police_score_snake=TTF_OpenFont("others/m01/m01.TTF",taille_px/2);
    SDL_Surface* texte_score=NULL;
    SDL_Rect position_score_snake;
    SDL_Rect position_score;
    position_score_snake.x=position_scoreboard.x+2*taille_px;
    position_score_snake.y=position_scoreboard.y+4*taille_px;
    SDL_Surface* square=SDL_CreateRGBSurface(0,taille_px,taille_px,32,0,0,0,0);
    char texte[23];
    char type[8];
    for(int i=0;i<nb_ser;i++){
        SDL_FillRect(square,NULL,SDL_MapRGB(screen->format,tab_couleur[i][0],tab_couleur[i][1],tab_couleur[i][2]));
        position_score_snake.y+=2*taille_px;
        SDL_BlitSurface(square,NULL,screen,&position_score_snake);
        SDL_Color couleur_score={tab_couleur[i][0],tab_couleur[i][1],tab_couleur[i][2]};
        position_score=position_score_snake;
        position_score.y=position_score_snake.y+(taille_px/4);
        position_score.x+=2*taille_px;
        switch(s[i].playType){
            case 0:
                sprintf(type,"Joueur");
                break;
            case 1:
                sprintf(type,"Idle");
                break;
            case 2:
                sprintf(type,"Défensif");
                break;
            case 3:
                sprintf(type,"Offensif");
                break;
            default:
                sprintf(type,"VACPLS");
                break;
            }
        sprintf(texte,"Snake(%s): %06d",type,(SDL_GetTicks()-tps_debut)/10);
        texte_score=TTF_RenderText_Solid(police_score_snake,texte,couleur_score);
        SDL_BlitSurface(texte_score,NULL,screen,&position_score);

    }
    SDL_FreeSurface(square);
    SDL_FreeSurface(texte_score);
}



