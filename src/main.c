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


int main(){
    if(SDL_Init(SDL_INIT_VIDEO)==-1){
        printf("Error sdl_init %s\n",SDL_GetError());
        return 1;
        }
    TTF_Init();
    SDL_Color couleurBlanche={255,255,255};
    const SDL_VideoInfo* videoInfo;
    videoInfo=SDL_GetVideoInfo();
    SDL_Event event;
    unsigned int maxW=videoInfo->current_w;
    unsigned int maxH=videoInfo->current_h;
    SDL_Surface* ecran=NULL;
    TTF_Font* police=NULL;
    SDL_Surface* texte=NULL;
    SDL_Rect positionTexte1;
    SDL_Rect positionTexte2;


    police=TTF_OpenFont("others/demolition_crack/Demolition_Crack.ttf",65);
    texte=TTF_RenderText_Blended(police,"1-JOUER",couleurBlanche);
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
    int continuer =1;
    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer=0;
                break;
            default:
                break;
            }
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            SDL_BlitSurface(texte,NULL,ecran,&positionTexte1);
            SDL_BlitSurface(texte2,NULL,ecran,&positionTexte2);
            SDL_Flip(ecran);

        }
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
    TTF_Quit();
    SDL_Quit();
    return 0;}
