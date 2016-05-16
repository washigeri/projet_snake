/**
 * @file main.c
 * @brief Main d'éxecution
 */


#include "struct.h"
#include "jeu.h"
#include "snake.h"
#include "affiche.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#define NB_MAX_SERPENT 8


snake* init_snakes(){
    snake* res=(snake*)calloc(NB_MAX_SERPENT,sizeof(snake));
    int taille_serpent=4;
    for(int i=0;i<NB_MAX_SERPENT;i++){
        if(i==0){
            res[i]=init_snake(taille_serpent,joueur);
            }
        else{
            res[i]=init_snake(taille_serpent,idle);
            }
        }
    return res;
    }

void placement_serpent(snake* res, int nbs, int taille_plateau){
    int espacement_vert_g=(taille_plateau)/(nbs/2+1);
    int espacement_vert_d=(taille_plateau)/(nbs-(nbs/2)+1);
    int taille_serpent=4;
    for(int i=0;i<nbs;i++){
        for(int k=0;k<taille_serpent;k++){
            if(i<(nbs/2)){
                res[i].pos[k].y=(i+1)*espacement_vert_g;
                res[i].pos[k].x=(taille_plateau/4)+(taille_serpent/2)-k;
                res[i].dir[0]=right;
                }
            else{
                res[i].pos[k].y=(i+1 - nbs/2)*espacement_vert_d;
                res[i].pos[k].x=(3*taille_plateau/4)-(taille_serpent/2)+k;
                res[i].dir[0]=left;
                }
            }
        }
    }


void reset_snakes(snake* snakes, int nb,int taille_p){
    for(int i=0;i<nb;i++){
        snakes[i].dead[0]=false;
    }
    placement_serpent(snakes, nb,taille_p);
}




int main(){
    int nbs=2;
    int difficulte=2;
    init_tab_couleur();
    plateau* p=init_plateau(30);
    snake* snakes=init_snakes();
    if(SDL_Init(SDL_INIT_VIDEO)==-1){
        printf("Error sdl_init %s\n",SDL_GetError());
        return 1;
    }
    TTF_Init();
    init_sprites();
    const SDL_VideoInfo* videoInfo;
    videoInfo=SDL_GetVideoInfo();
    SDL_Event event;
    SDL_Event event_debut_partie;
    unsigned int maxW=videoInfo->current_w;
    unsigned int maxH=videoInfo->current_h;
    SDL_Surface* ecran=NULL;
    ecran=SDL_SetVideoMode(maxW,maxH,32, SDL_RESIZABLE | SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Snake vs Schlangà",NULL);
    if(ecran==NULL){
        printf("Error sdl_setvideomode %s\n",SDL_GetError());
        return 1;
    }
    int continuer=1;
    int selecteur=0;
    int selecteur_options=0;
    int demarrer_jeu=1;
    SDLKey touche;
    placement_serpent(snakes,nbs,p->taille);
    int temps_debut;
    while(continuer){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    continuer=0;
                    break;
                case SDL_KEYDOWN:
                    touche=event.key.keysym.sym;
                    switch(touche){
                        case SDLK_KP1:
                            if(selecteur==0)
                                selecteur=1;
                            break;
                        case SDLK_AMPERSAND:
                            if(selecteur==0)
                                selecteur=1;
                            break;
                        case SDLK_KP2:
                            if(selecteur==0)
                                selecteur=2;
                            break;
                        case SDLK_KP3:
                            if(selecteur==0)
                                selecteur=3;
                            break;
                        case SDLK_ESCAPE:
                            if(selecteur==1)
                                selecteur=4;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        switch(selecteur){
            case 0:
                demarrer_jeu=1;
                load_menu_sdl(ecran);
                break;
            case 1:
                affiche_sdl(ecran,snakes,nbs,*p,SDL_GetTicks());
                while(demarrer_jeu){
                    SDL_Flip(ecran);
                    SDL_WaitEvent(&event_debut_partie);
                    SDLKey input=event_debut_partie.key.keysym.sym;
                    if(input==SDLK_DOWN || input==SDLK_s || input==SDLK_UP || input==SDLK_z || input==SDLK_LEFT || input==SDLK_q || input==SDLK_RIGHT || input==SDLK_d)
                    {
                        touche=event_debut_partie.key.keysym.sym;
                        demarrer_jeu=0;
                        temps_debut=SDL_GetTicks();
                    }
                }
                bools jouer=win(jouer_sdl(ecran,snakes,nbs,p,touche,difficulte,temps_debut),snakes,nbs);
                if(!jouer.b){
                    demarrer_jeu=1;
                    selecteur=fin_partie_sdl(ecran,jouer,snakes,nbs,*p,temps_debut);
                    reset_snakes(snakes,nbs,p->taille);
                }
                break;
            case 2:
                selecteur_options=load_options_sdl(ecran,snakes,*p,&difficulte,&nbs,touche,selecteur_options,&continuer,&selecteur);
                placement_serpent(snakes,nbs,p->taille);
                break;
            case 3:
                continuer=0;
                break;
            case 4:
                selecteur=load_pause(ecran,p->taille,&temps_debut);
                if(!selecteur)
                    reset_snakes(snakes,nbs,p->taille);
                break;
            default:
                break;
        }
    SDL_Flip(ecran);

    }
    TTF_Quit();
    SDL_Quit();
    effacer_Partie(p,snakes,nbs);
    return 0;
}

