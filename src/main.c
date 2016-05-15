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

snake* init_snakes(int n,int taille_plateau){
    int espacement_vert_g=(taille_plateau)/(n/2+1);
    int espacement_vert_d=(taille_plateau)/(n-(n/2)+1);
    int taille_serpent=4;
    snake* res=(snake*)calloc(n,sizeof(snake));
    for(int i=0;i<n;i++){
        if(i==0){
            res[i]=init_snake(taille_serpent,joueur);
            }
        else{
            res[i]=init_snake(taille_serpent,idle);
            }
        for(int k=0;k<taille_serpent;k++){

            if(i<(n/2)){
                res[i].pos[k].y=(i+1)*espacement_vert_g;
                res[i].pos[k].x=(taille_plateau/4)+(taille_serpent/2)-k;
                res[i].dir[0]=right;
                }
            else{
                res[i].pos[k].y=(i+1-n/2)*espacement_vert_d;
                res[i].pos[k].x=(3*taille_plateau/4)-(taille_serpent/2)+k;
                res[i].dir[0]=left;
                }
            }
        }
    return res;
    }


#define NB_SERPENT 8

void reset_snakes(snake* snakes, int nb,int taille_p){
    for(int i=0;i<nb;i++){
        delete_snake(snakes + i);
    }
    free(snakes);
    snakes=init_snakes(nb,taille_p);
}



int main(){
    init_tab_couleur();
    plateau p=init_plateau(30);
    snake* snakes=init_snakes(NB_SERPENT,p.taille);
    snakes[1].playType=idle;
    if(SDL_Init(SDL_INIT_VIDEO)==-1){
        printf("Error sdl_init %s\n",SDL_GetError());
        return 1;
    }
    TTF_Init();
    SDL_Color couleurBlanche={255,255,255};
    const SDL_VideoInfo* videoInfo;
    videoInfo=SDL_GetVideoInfo();
    SDL_Event event;
    SDL_Event event_debut_partie;
    SDL_Event event_fin_partie;
    unsigned int maxW=videoInfo->current_w;
    unsigned int maxH=videoInfo->current_h;
    SDL_Surface* ecran=NULL;
    TTF_Font* police=NULL;
    SDL_Rect positionTexte1;
    SDL_Rect positionTexte2;
    police=TTF_OpenFont("others/demolition_crack/Demolition_Crack.ttf",65);
    SDL_Surface* texte=TTF_RenderText_Blended(police,"1-JOUER",couleurBlanche);
    SDL_Surface* texte2=TTF_RenderText_Blended(police,"2-OPTIONS",couleurBlanche);
    ecran=SDL_SetVideoMode(maxW,maxH,32, SDL_RESIZABLE | SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Snake vs Schlangà",NULL);
    if(ecran==NULL){
        printf("Error sdl_setvideomode %s\n",SDL_GetError());
        return 1;
    }
    positionTexte1.x=(ecran->w/2)-(texte->w/2);
    positionTexte1.y=(ecran->h/2)-(texte->h/2);
    positionTexte2.x=positionTexte1.x;
    positionTexte2.y=positionTexte1.y+(texte2->h);
    int continuer=1;
    int selecteur=0;
    int demarrer_jeu=1;
    int retour_menu=1;
    SDLKey touche;
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
                            selecteur=1;
                            break;
                        case SDLK_AMPERSAND:
                            selecteur=1;
                            break;
                        case SDLK_KP2:
                            selecteur=2;
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
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(texte,NULL,ecran,&positionTexte1);
                SDL_BlitSurface(texte2,NULL,ecran,&positionTexte2);
                break;
            case 1:
                retour_menu=1;
                affiche_sdl(ecran,snakes,NB_SERPENT,p,SDL_GetTicks());
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
                bools* jouer = jouer_sdl(ecran,snakes,NB_SERPENT,p,touche,1,temps_debut);
                if(!win(jouer,snakes,NB_SERPENT).b){
                    demarrer_jeu=1;
                    reset_snakes(snakes,NB_SERPENT,p.taille);
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
                }
                break;
            case 2:
                continuer=0;
                break;
            default:
                break;
        }
        SDL_Flip(ecran);
    }
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
    TTF_Quit();
    SDL_Quit();
    effacer_Partie(&p,snakes,NB_SERPENT);
    return 0;
}
