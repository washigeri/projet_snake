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
            else if( p.cases[i][j]==2 ){
                printf("@-");
            }
            else if( p.cases[i][j]==3 ){
                printf("&-");
            }
            else if( p.cases[i][j]==4 ){
                printf("()");
            }
            else if( p.cases[i][j]==5 ){
                printf(")(");
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


int tab_couleur[NB_MAX_SERPENT][3];
int taille_cases_px;

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
    fclose(fichier);
}





void score_snakes_sdl(SDL_Surface* screen, snake* s, int nb_ser, plateau p,int tps_debut, int taille_px, SDL_Rect position_scoreboard){
    TTF_Font* police_score_snake=NULL;
    police_score_snake=TTF_OpenFont("others/m01/m01.TTF",taille_px/2);
    SDL_Surface* texte_score=NULL;
    SDL_Surface* tdm=NULL;
    tdm=IMG_Load("others/sprites/tdmtaille30.png");
    SDL_Rect position_score_snake;
    SDL_Rect position_score;
    position_score_snake.x=position_scoreboard.x+2*taille_px;
    position_score_snake.y=position_scoreboard.y+4*taille_px;
    SDL_Surface* square=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_px,taille_px,32,0,0,0,0);
    char texte[23];
    char type[8];
    for(int i=0;i<nb_ser;i++){
        position_score_snake.y+=2*taille_px;
        if(!s[i].dead[0]){
            SDL_FillRect(square,NULL,SDL_MapRGB(screen->format,tab_couleur[i][0],tab_couleur[i][1],tab_couleur[i][2]));
            SDL_BlitSurface(square,NULL,screen,&position_score_snake);
        }
        else{
            SDL_BlitSurface(tdm,NULL,screen,&position_score_snake);
        }
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
        if(!s[i].dead[0]){
            s[i].score[0]=(SDL_GetTicks()-tps_debut)/10;
        }
        sprintf(texte,"Snake(%s): %06d",type,s[i].score[0]);
        texte_score=TTF_RenderText_Solid(police_score_snake,texte,couleur_score);
        SDL_BlitSurface(texte_score,NULL,screen,&position_score);
    }
    SDL_FreeSurface(square);
    SDL_FreeSurface(texte_score);
    TTF_CloseFont(police_score_snake);
}

void affiche_sdl(SDL_Surface* screen, snake* s, int nbs, plateau p,int temps_debut){
    taille_cases_px=screen->h/p.taille;
    SDL_Surface* wall=NULL;
    SDL_Surface* snake=NULL;
    SDL_Surface* score=NULL;
    SDL_Rect position_score_board;
    SDL_Surface* score_board=NULL;
    TTF_Font* police=TTF_OpenFont("others/m01/m01.TTF",taille_cases_px);
    position_score_board.y=0;position_score_board.x=taille_cases_px*(p.taille);
    char score_ch[14];
    SDL_Color color_white={255,255,255};
    int temps=(SDL_GetTicks()-temps_debut)/1000;
    sprintf(score_ch,"TEMPS: %d s",temps);
    score=TTF_RenderText_Solid(police,score_ch,color_white);
    wall=IMG_Load("others/sprites/sprite_bricks_tutorial_1_25px.png");
    snake=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px,taille_cases_px,32,0,0,0,0);
    score_board=SDL_CreateRGBSurface(SDL_HWSURFACE,(screen->w)-position_score_board.x,screen->h,32,0,0,0,0);
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
        if(!s[k].dead[0]){
            SDL_FillRect(snake,NULL,SDL_MapRGB(screen->format,tab_couleur[k][0],tab_couleur[k][1],tab_couleur[k][2]));
            for(i=0;i<s[k].taille;i++){
                position_snake.x=s[k].pos[i].x*taille_cases_px;
                position_snake.y=s[k].pos[i].y*taille_cases_px;
                SDL_BlitSurface(snake,NULL,screen,&position_snake);
            }
        }
    }
    SDL_BlitSurface(score_board,NULL,screen,&position_score_board);
    position_score.x=position_score_board.x+taille_cases_px;
    position_score.y=taille_cases_px;
    SDL_BlitSurface(score,NULL,screen,&position_score);
    score_snakes_sdl(screen,s,nbs,p,temps_debut,taille_cases_px,position_score_board);
    SDL_FreeSurface(snake);
    SDL_FreeSurface(score);
    SDL_FreeSurface(score_board);
    TTF_CloseFont(police);
}



void load_menu_sdl(SDL_Surface* screen){
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_Color couleurBlanche={255,255,255};
    TTF_Font* police=NULL;
    TTF_Font* policeTitre=NULL;
    SDL_Rect positionTexte1;
    SDL_Rect positionTexte2;
    SDL_Rect positionTexte3;
    SDL_Rect positionTexte4;
    police=TTF_OpenFont("others/mario_font/mario.ttf",50);
    policeTitre=TTF_OpenFont("others/mario_font/mario.ttf",90);
    SDL_Surface* texte1=TTF_RenderText_Blended(police,"1 - JOUER",couleurBlanche);
    SDL_Surface* texte2=TTF_RenderText_Blended(police,"2 - OPTIONS",couleurBlanche);
    SDL_Surface* texte3=TTF_RenderText_Blended(police,"3 - QUITTER",couleurBlanche);
    SDL_Surface* texte4=TTF_RenderText_Blended(policeTitre,"SNAKE vs SCHLANGA",couleurBlanche);
    positionTexte1.x=screen->w/2-texte1->w/2;
    positionTexte2.x=screen->w/2-texte2->w/2;
    positionTexte3.x=screen->w/2-texte3->w/2;
    positionTexte4.x=screen->w/2-texte4->w/2;
    positionTexte1.y=2*screen->h/3;
    positionTexte2.y=2*screen->h/3+texte1->h+texte2->h/2;
    positionTexte3.y=positionTexte2.y+texte2->h+texte3->h/2;
    positionTexte4.y=2*texte4->h/3;
    taille_cases_px=25;
    int taille_1_snake=screen->w/(taille_cases_px*5);
    SDL_Surface *snake_1=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px*taille_1_snake,taille_cases_px,32,0,0,0,0);
    SDL_FillRect(snake_1,NULL,SDL_MapRGB(screen->format,0,255,0));
    int taille_2_snake=screen->w/(taille_cases_px*10);
    SDL_Surface *snake_2=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px*taille_2_snake,taille_cases_px,32,0,0,0,0);
    SDL_FillRect(snake_2,NULL,SDL_MapRGB(screen->format,0,255,0));
    int taille_3_snake=screen->h/(taille_cases_px*10);
    SDL_Surface *snake_3=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px,taille_cases_px*taille_3_snake,32,0,0,0,0);
    SDL_FillRect(snake_3,NULL,SDL_MapRGB(screen->format,0,255,0));
    SDL_Rect position_snake_1;
    SDL_Rect position_snake_2;
    SDL_Rect position_snake_3;
    position_snake_1.x=screen->w/8;
    position_snake_1.y=screen->h/3;
    position_snake_3.x=position_snake_1.x+snake_1->w;
    position_snake_3.y=position_snake_1.y;
    position_snake_2.x=position_snake_1.x+snake_1->w;
    position_snake_2.y=position_snake_3.y+snake_3->h;
    int taille_1_schlanga=screen->w/(taille_cases_px*4);
    SDL_Surface *schlanga_1=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px*taille_1_schlanga,taille_cases_px,32,0,0,0,0);
    SDL_FillRect(schlanga_1,NULL,SDL_MapRGB(screen->format,255,0,0));
    int taille_2_schlanga=screen->h/(taille_cases_px*7);
    SDL_Surface *schlanga_2=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px,taille_cases_px*taille_2_schlanga,32,0,0,0,0);
    SDL_FillRect(schlanga_2,NULL,SDL_MapRGB(screen->format,255,0,0));
    SDL_Rect position_schlanga_1;
    SDL_Rect position_schlanga_2;
    position_schlanga_1.x=screen->w/2;
    position_schlanga_1.y=position_snake_2.y;
    position_schlanga_2.x=position_schlanga_1.x;
    position_schlanga_2.y=position_schlanga_1.y;
    SDL_BlitSurface(snake_1,NULL,screen,&position_snake_1);
    SDL_BlitSurface(snake_2,NULL,screen,&position_snake_2);
    SDL_BlitSurface(snake_3,NULL,screen,&position_snake_3);
    SDL_BlitSurface(schlanga_1,NULL,screen,&position_schlanga_1);
    SDL_BlitSurface(schlanga_2,NULL,screen,&position_schlanga_2);
    SDL_BlitSurface(texte1,NULL,screen,&positionTexte1);
    SDL_BlitSurface(texte2,NULL,screen,&positionTexte2);
    SDL_BlitSurface(texte3,NULL,screen,&positionTexte3);
    SDL_BlitSurface(texte4,NULL,screen,&positionTexte4);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(texte4);
    SDL_FreeSurface(snake_1);
    SDL_FreeSurface(snake_2);
    SDL_FreeSurface(snake_3);
    SDL_FreeSurface(schlanga_1);
    SDL_FreeSurface(schlanga_2);
    TTF_CloseFont(police);
    TTF_CloseFont(policeTitre);
}

int load_options_sdl(SDL_Surface* screen, snake* snakes, plateau p, int* difficulte, int* nbs,SDLKey touche,int selecteur_position, int* continuer, int* selecteur_menu){
    taille_cases_px=screen->h/p.taille;

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_Color couleurBlanche={255,255,255};
    TTF_Font* police=TTF_OpenFont("others/m01/m01.TTF",taille_cases_px*0.9);
    SDL_Surface* texte_nb_ser_jeu=TTF_RenderText_Blended(police,"Nombre de snakes en jeu: ",couleurBlanche);
    char buffer[1]; sprintf(buffer,"%d",(*nbs));
    SDL_Surface* texte_nb_ser=TTF_RenderText_Blended(police,buffer,couleurBlanche);
    SDL_Surface* texte_vitesse_jeu=TTF_RenderText_Blended(police,"Vitesse de jeu: ",couleurBlanche);
    char buffer2[2];
    sprintf(buffer2,"%d",(*difficulte));
    SDL_Surface* texte_vitesse=TTF_RenderText_Blended(police,buffer2,couleurBlanche);
    SDL_Surface* texte_type_snakes=TTF_RenderText_Blended(police,"Choix des types de serpents: ",couleurBlanche);
    SDL_Surface* snakes_surfaces[NB_MAX_SERPENT][3];
    char buffer3[16];
    char type[8];
    for(int i=0;i<(*nbs);i++){
        switch(snakes[i].playType){
            case joueur:
                sprintf(type,"Joueur");
                break;
            case idle:
                sprintf(type,"Idle");
                break;
            case defensif:
                sprintf(type,"Defensif");
                break;
            case offensif:
                sprintf(type,"Offensif");
                break;

            }
            sprintf(buffer3,"Snake %d %s",i+1,type);
            snakes_surfaces[i][0]=TTF_RenderText_Blended(police,buffer3,couleurBlanche);
            snakes_surfaces[i][1]=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px,taille_cases_px,32,0,0,0,0);
            SDL_FillRect(snakes_surfaces[i][1],NULL,SDL_MapRGB(screen->format,tab_couleur[i][0],tab_couleur[i][1],tab_couleur[i][2]));
            snakes_surfaces[i][2]=TTF_RenderText_Blended(police,type,couleurBlanche);
        }
    SDL_Rect positionTexte_nb_ser_jeu,positionTexte_nb_ser,positionTexte_vitesse_jeu,positionTexte_vitesse,positionTexte_type_snakes,positionSnakes_surface[8];
    int ecart_hauteur=screen->h/11;
    positionTexte_nb_ser_jeu.y=0+texte_nb_ser_jeu->h/2.0; positionTexte_nb_ser_jeu.x=screen->w/4.0-texte_nb_ser_jeu->w/2.0;
    positionTexte_nb_ser.y=0+texte_nb_ser->h/2.0; positionTexte_nb_ser.x=screen->w*(3.0/4.0)-texte_nb_ser->w/2.0;
    positionTexte_vitesse_jeu.y=ecart_hauteur+texte_vitesse_jeu->h/2; positionTexte_vitesse_jeu.x=screen->w/4-texte_vitesse_jeu->w/2.0;
    positionTexte_vitesse.y=ecart_hauteur+texte_vitesse->h/2; positionTexte_vitesse.x=screen->w*(3.0/4.0)-texte_vitesse->w/2.0;
    positionTexte_type_snakes.y=2*ecart_hauteur+texte_type_snakes->h/2; positionTexte_type_snakes.x=screen->w/4.0-texte_type_snakes->w/2.0;
    for(int j=0;j<(*nbs);j++){
        positionSnakes_surface[j].y=(j+3)*ecart_hauteur+snakes_surfaces[j][0]->h/2;
        positionSnakes_surface[j].x=0;
        }
    SDL_BlitSurface(texte_nb_ser_jeu,NULL,screen,&positionTexte_nb_ser_jeu);
    SDL_BlitSurface(texte_nb_ser,NULL,screen,&positionTexte_nb_ser);
    SDL_BlitSurface(texte_vitesse_jeu,NULL,screen,&positionTexte_vitesse_jeu);
    SDL_BlitSurface(texte_vitesse,NULL,screen,&positionTexte_vitesse);
    SDL_BlitSurface(texte_type_snakes,NULL,screen,&positionTexte_type_snakes);
    SDL_Rect temp;
    for(int k=0;k<(*nbs);k++){
        temp.y=positionSnakes_surface[k].y;
        temp.x=screen->w/4.0-snakes_surfaces[k][0]->w/2.0;
        SDL_BlitSurface(snakes_surfaces[k][0],NULL,screen,&temp);
        temp.x=screen->w*(2.0/4.0)-snakes_surfaces[k][1]->w/2.0;
        SDL_BlitSurface(snakes_surfaces[k][1],NULL,screen,&temp);
        temp.x=screen->w*(3.0/4.0)-snakes_surfaces[k][2]->w/2.0;
        SDL_BlitSurface(snakes_surfaces[k][2],NULL,screen,&temp);
        }
    SDL_Surface* selecteur=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px,taille_cases_px,32,0,0,0,0);
    SDL_FillRect(selecteur,NULL,SDL_MapRGB(screen->format,255,255,255));
    SDL_Rect positionSelecteur;
    int nombre_serpent=(*nbs);
    int vitesse=(*difficulte);
    SDL_Event event;
    if(SDL_WaitEvent(&event)){
        touche=event.key.keysym.sym;
        switch(event.type)
        {
            case SDL_QUIT:
                (*continuer)=0;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        (*selecteur_menu)=0;
                    break;
                    case SDLK_RETURN:
                        (*selecteur_menu)=0;
                    break;
                    default:
                        break;
                    }
            }
        switch(selecteur_position)
        {
            case 0:
                positionSelecteur.x=taille_cases_px;positionSelecteur.y=texte_nb_ser_jeu->h/2;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if(event.type==SDL_KEYDOWN){
                switch(touche){
                    case SDLK_DOWN:
                        selecteur_position=1;
                        break;
                    case SDLK_LEFT:
                        if(nombre_serpent<=8 && nombre_serpent>1)
                            nombre_serpent--;
                        break;
                    case SDLK_RIGHT:
                        if(nombre_serpent>=1 && nombre_serpent<8)
                            nombre_serpent++;
                        break;
                    case SDLK_UP:
                        selecteur_position=nombre_serpent;
                    default:
                        break;
                    }
                }
                break;
            case 1:
                positionSelecteur.x=taille_cases_px;positionSelecteur.y=texte_vitesse_jeu->h/2+ecart_hauteur;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if(event.type==SDL_KEYDOWN){
                switch(touche){
                        case SDLK_DOWN:
                            selecteur_position=2;
                            break;
                        case SDLK_UP:
                            selecteur_position=0;
                            break;
                        case SDLK_LEFT:
                            if(vitesse>1 && vitesse<=3)
                                vitesse--;
                            break;
                        case SDLK_RIGHT:
                            if(vitesse>=1 && vitesse<3)
                                vitesse++;
                            break;
                        default:
                            break;
                            }
                        }
                    break;
            case 2:
                positionSelecteur.x=taille_cases_px; positionSelecteur.y=snakes_surfaces[1][0]->h/2+4*ecart_hauteur;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if(event.type == SDL_KEYDOWN){
                switch(touche){
                    case SDLK_DOWN:
                        if(nombre_serpent>2)
                            selecteur_position=3;
                        else
                            selecteur_position=0;
                        break;
                    case SDLK_UP:
                        selecteur_position=1;
                        break;
                    case SDLK_LEFT:
                        if(snakes[1].playType>1 && snakes[1].playType<=3)
                            snakes[1].playType--;
                        break;
                    case SDLK_RIGHT:
                        if(snakes[1].playType<3 && snakes[1].playType>=1)
                            snakes[1].playType++;

                    default:
                        break;
                    }
                }
                break;

            case 3:
                positionSelecteur.x=taille_cases_px; positionSelecteur.y=snakes_surfaces[2][0]->h/2+5*ecart_hauteur;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if(event.type == SDL_KEYDOWN){
                    switch(touche){
                        case SDLK_DOWN:
                            if(nombre_serpent>3)
                                selecteur_position=4;
                            else
                                selecteur_position=0;
                            break;
                        case SDLK_UP:
                            selecteur_position=2;
                            break;
                        case SDLK_LEFT:
                            if(snakes[2].playType>1 && snakes[2].playType<=3)
                                snakes[2].playType--;
                            break;
                        case SDLK_RIGHT:
                            if(snakes[2].playType<3 && snakes[2].playType>=1)
                                snakes[2].playType++;
                            break;
                        default:
                            break;

                        }
                    }
                break;
            case 4:
                positionSelecteur.x=taille_cases_px; positionSelecteur.y=snakes_surfaces[3][0]->h/2+6*ecart_hauteur;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if(event.type == SDL_KEYDOWN){
                    switch(touche){
                        case SDLK_DOWN:
                            if(nombre_serpent>4)
                                selecteur_position=5;
                            else
                                selecteur_position=0;
                            break;
                        case SDLK_UP:
                            selecteur_position=3;
                            break;
                        case SDLK_LEFT:
                            if(snakes[3].playType>1 && snakes[3].playType<=3)
                                snakes[3].playType--;
                            break;
                        case SDLK_RIGHT:
                            if(snakes[3].playType<3 && snakes[3].playType>=1)
                                snakes[3].playType++;
                            break;
                        default:
                            break;

                        }
                    }
                break;
            case 5:
                positionSelecteur.x=taille_cases_px; positionSelecteur.y=snakes_surfaces[4][0]->h/2 + 7*ecart_hauteur;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if(event.type == SDL_KEYDOWN){
                    switch(touche){
                        case SDLK_DOWN:
                            if(nombre_serpent>5)
                                selecteur_position=6;
                            else
                                selecteur_position=0;
                            break;
                        case SDLK_UP:
                            selecteur_position=4;
                            break;
                        case SDLK_LEFT:
                            if(snakes[4].playType>1 && snakes[4].playType<=3)
                                snakes[4].playType--;
                            break;
                        case SDLK_RIGHT:
                            if(snakes[4].playType<3 && snakes[4].playType>=1)
                                snakes[4].playType++;
                            break;
                        default:
                            break;

                    }
                }
            break;

            case 6:
                positionSelecteur.x=taille_cases_px; positionSelecteur.y = snakes_surfaces[5][0]->h/2 + 8*ecart_hauteur;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if( event.type == SDL_KEYDOWN){
                    switch(touche){
                        case SDLK_DOWN:
                            if(nombre_serpent>6)
                                selecteur_position=7;
                            else
                                selecteur_position=0;
                            break;
                        case SDLK_UP:
                            selecteur_position=5;
                            break;
                        case SDLK_LEFT:
                            if(snakes[5].playType>1 && snakes[5].playType<=3)
                                snakes[5].playType--;
                            break;
                        case SDLK_RIGHT:
                            if(snakes[5].playType<3 && snakes[5].playType>=1)
                                snakes[5].playType++;
                            break;
                        default:
                            break;

                        }
                    }
                break;
            case 7:
                positionSelecteur.x=taille_cases_px; positionSelecteur.y = snakes_surfaces[6][0] -> h/2 + 9*ecart_hauteur;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if( event.type == SDL_KEYDOWN){
                    switch(touche){
                        case SDLK_DOWN:
                            if(nombre_serpent>7)
                                selecteur_position=8;
                            else
                                selecteur_position=0;
                            break;
                        case SDLK_UP:
                            selecteur_position=6;
                        break;
                        case SDLK_LEFT:
                            if(snakes[6].playType>1 && snakes[6].playType<=3)
                                snakes[6].playType--;
                            break;
                        case SDLK_RIGHT:
                            if(snakes[6].playType<3 && snakes[6].playType>=1)
                                snakes[6].playType++;
                            break;
                        default:
                            break;
                      }
                    }
                break;
            case 8:
                positionSelecteur.x=taille_cases_px; positionSelecteur.y = snakes_surfaces[7][0] -> h/2 + 10*ecart_hauteur;
                SDL_BlitSurface(selecteur,NULL,screen,&positionSelecteur);
                if( event.type == SDL_KEYDOWN){
                    switch(touche){
                        case SDLK_DOWN:
                            selecteur_position=0;
                            break;
                        case SDLK_UP:
                            selecteur_position=7;
                        break;
                        case SDLK_LEFT:
                            if(snakes[7].playType>1 && snakes[7].playType<=3)
                                snakes[7].playType--;
                            break;
                        case SDLK_RIGHT:
                            if(snakes[7].playType<3 && snakes[7].playType>=1)
                                snakes[7].playType++;
                            break;
                        default:
                            break;
                      }
                    }
                break;
        }

    }

    //filledTrigonRGBA(screen,positionTexte_nb_ser_jeu.x,positionTexte_nb_ser_jeu.y,positionTexte_nb_ser_jeu.x,positionTexte_nb_ser_jeu.y+texte_nb_ser_jeu->h,positionTexte_nb_ser_jeu.x+texte_nb_ser_jeu->h/2,positionTexte_nb_ser_jeu.y+texte_nb_ser_jeu->h/2,255,255,255,255);
    TTF_CloseFont(police);
    SDL_FreeSurface(texte_nb_ser);
    SDL_FreeSurface(texte_nb_ser_jeu);
    SDL_FreeSurface(texte_vitesse_jeu);
    SDL_FreeSurface(texte_vitesse);
    SDL_FreeSurface(texte_type_snakes);
    SDL_FreeSurface(selecteur);
    for(int i=0;i<(*nbs);i++){
        SDL_FreeSurface(snakes_surfaces[i][0]);
        SDL_FreeSurface(snakes_surfaces[i][1]);
        SDL_FreeSurface(snakes_surfaces[i][2]);

    }
    (*nbs)=nombre_serpent;
    (*difficulte)=vitesse;
    return selecteur_position;
}

int load_pause(SDL_Surface* screen,int taille_plateau,int* temps_debut){
    int debut=SDL_GetTicks();
    taille_cases_px=screen->h/taille_plateau;
    SDL_Surface* surface=SDL_CreateRGBSurface(SDL_HWSURFACE,(screen->h)/2,(screen->h)/3,32,0,0,0,0);
    SDL_Rect position;
    position.x=(screen->h)/2-(surface->w)/2;
    position.y=(screen->h)/2-(surface->h)/2;
    SDL_FillRect(surface,NULL,SDL_MapRGB(screen->format,255,255,255));
    SDL_BlitSurface(surface,NULL,screen,&position);
    SDL_Color couleurNoire={0,0,0};
    TTF_Font* police=NULL;
    police=TTF_OpenFont("others/m01/m01.TTF",taille_cases_px/2);
    SDL_Rect positionTexte1;
    SDL_Rect positionTexte2;
    SDL_Rect positionTexte3;
    SDL_Surface* texte3=TTF_RenderText_Blended(police,"PAUSE",couleurNoire);
    SDL_Surface* texte1=TTF_RenderText_Blended(police,"1-REPRENDRE",couleurNoire);
    SDL_Surface* texte2=TTF_RenderText_Blended(police,"2-REVENIR AU MENU",couleurNoire);
    positionTexte1.x=position.x+(surface->w)/2-(texte1->w)/2;
    positionTexte1.y=position.y+(surface->h)/2-(texte1->h)/2;
    positionTexte2.x=position.x+(surface->w)/2-(texte2->w)/2;
    positionTexte2.y=position.y+(surface->h)/2-(texte2->h)/2+taille_cases_px;
    positionTexte3.x=position.x+(surface->w)/2-(texte3->w)/2;
    positionTexte3.y=position.y+(surface->h)/2-(texte3->h)/2-2*taille_cases_px;
    SDL_BlitSurface(texte1,NULL,screen,&positionTexte1);
    SDL_BlitSurface(texte2,NULL,screen,&positionTexte2);
    SDL_BlitSurface(texte3,NULL,screen,&positionTexte3);
    SDL_Surface* contour_horizontal=SDL_CreateRGBSurface(SDL_HWSURFACE,surface->w+taille_cases_px,taille_cases_px/2,32,0,0,0,0);
    SDL_Surface* contour_vertical=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px/2,surface->h,32,0,0,0,0);
    SDL_FillRect(contour_horizontal,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_FillRect(contour_vertical,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_Rect position_contour_hor;
    SDL_Rect position_contour_vert;
    position_contour_hor.x=position.x-taille_cases_px/2;
    position_contour_hor.y=position.y-taille_cases_px/2;
    position_contour_vert.x=position.x-taille_cases_px/2;
    position_contour_vert.y=position.y;
    SDL_BlitSurface(contour_horizontal,NULL,screen,&position_contour_hor);
    SDL_BlitSurface(contour_vertical,NULL,screen,&position_contour_vert);
    position_contour_hor.y=position.y+surface->h;
    position_contour_vert.x=position.x+surface->w;
    SDL_BlitSurface(contour_horizontal,NULL,screen,&position_contour_hor);
    SDL_BlitSurface(contour_vertical,NULL,screen,&position_contour_vert);
    SDL_Flip(screen);
    int selecteur;
    SDL_Event event;
    int pause=1;
    while(pause){
        SDL_WaitEvent(&event);
        switch(event.key.keysym.sym){
            case SDLK_KP1:
                selecteur=1;
                pause=0;
                break;
            case SDLK_AMPERSAND:
                selecteur=1;
                pause=0;
                break;
            case SDLK_KP2:
                selecteur=0;
                pause=0;
                break;
            default:
                break;
        }

    }
    int fin=SDL_GetTicks();
    (*temps_debut)+=(fin-debut);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(contour_horizontal);
    SDL_FreeSurface(contour_vertical);
    return selecteur;
}

int fin_partie_sdl(SDL_Surface* screen, bools resultat_partie, snake* snakes,int nbs, plateau p,int temps_debut){
    affiche_sdl(screen,snakes,nbs,p,temps_debut);
    taille_cases_px=screen->h/p.taille;
    SDL_Surface* surface=SDL_CreateRGBSurface(SDL_HWSURFACE,(screen->h)/2,(screen->h)/3,32,0,0,0,0);
    SDL_Rect position;
    position.x=(screen->h)/2-(surface->w)/2;
    position.y=(screen->h)/2-(surface->h)/2;
    SDL_FillRect(surface,NULL,SDL_MapRGB(screen->format,255,255,255));
    SDL_BlitSurface(surface,NULL,screen,&position);
    SDL_Color couleurNoire={0,0,0};
    TTF_Font* police=NULL;
    police=TTF_OpenFont("others/m01/m01.TTF",taille_cases_px/2);
    SDL_Surface* texte1;
    SDL_Rect positionTexte1;
    SDL_Rect positionTexte2;
    SDL_Rect positionTexte3;
    SDL_Surface* texte2=TTF_RenderText_Blended(police,"1-REJOUER",couleurNoire);
    SDL_Surface* texte3=TTF_RenderText_Blended(police,"2-MENU",couleurNoire);
    positionTexte2.x=position.x+(surface->w)/2-(texte2->w)/2;
    positionTexte2.y=position.y+(surface->h)/2-(texte2->h)/2;
    positionTexte3.x=position.x+(surface->w)/2-(texte3->w)/2;
    positionTexte3.y=position.y+(surface->h)/2-(texte3->h)/2+taille_cases_px;
    if(!egalite_snake(resultat_partie.s,snakes[0])){
        texte1=TTF_RenderText_Blended(police,"VICTOIRE",couleurNoire);
        positionTexte1.x=position.x+(surface->w)/2-(texte1->w)/2;
        positionTexte1.y=position.y+(surface->h)/2-(texte1->h)/2-2*taille_cases_px;
        SDL_BlitSurface(texte1,NULL,screen,&positionTexte1);
    }
    else{
        texte1=TTF_RenderText_Blended(police,"GAME OVER",couleurNoire);
        positionTexte1.x=position.x+(surface->w)/2-(texte1->w)/2;
        positionTexte1.y=position.y+(surface->h)/2-(texte1->h)/2-2*taille_cases_px;
        SDL_BlitSurface(texte1,NULL,screen,&positionTexte1);
    }
    SDL_BlitSurface(texte2,NULL,screen,&positionTexte2);
    SDL_BlitSurface(texte3,NULL,screen,&positionTexte3);
    SDL_Surface* contour_horizontal=SDL_CreateRGBSurface(SDL_HWSURFACE,surface->w+taille_cases_px,taille_cases_px/2,32,0,0,0,0);
    SDL_Surface* contour_vertical=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_cases_px/2,surface->h,32,0,0,0,0);
    SDL_FillRect(contour_horizontal,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_FillRect(contour_vertical,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_Rect position_contour_hor;
    SDL_Rect position_contour_vert;
    position_contour_hor.x=position.x-taille_cases_px/2;
    position_contour_hor.y=position.y-taille_cases_px/2;
    position_contour_vert.x=position.x-taille_cases_px/2;
    position_contour_vert.y=position.y;
    SDL_BlitSurface(contour_horizontal,NULL,screen,&position_contour_hor);
    SDL_BlitSurface(contour_vertical,NULL,screen,&position_contour_vert);
    position_contour_hor.y=position.y+surface->h;
    position_contour_vert.x=position.x+surface->w;
    SDL_BlitSurface(contour_horizontal,NULL,screen,&position_contour_hor);
    SDL_BlitSurface(contour_vertical,NULL,screen,&position_contour_vert);
    SDL_Flip(screen);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(contour_horizontal);
    SDL_FreeSurface(contour_vertical);
    SDL_Event event_fin_partie;
    int retour_menu=1;
    int selecteur=1;
    while(retour_menu){
        SDL_WaitEvent(&event_fin_partie);
        switch(event_fin_partie.key.keysym.sym){
            case SDLK_KP1:
                retour_menu=0;
                break;
            case SDLK_KP2:
                selecteur=0;
                retour_menu=0;
                break;
            default:
                break;
        }
    }
    return selecteur;
}

