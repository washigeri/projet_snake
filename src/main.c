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
    int espacement_vert_g=(taille_plateau)*(2/n);
    int espacement_vert_d=(taille_plateau)/(n-(n/2));
    int taille_serpent=4;
    snake* res=(snake*)calloc(n,sizeof(snake));
    for(int i=0;i<n;i++){
        res[i]=init_snake(taille_serpent,joueur);
        for(int k=0;k<taille_serpent;k++){

            if(i<(n/2)){
                res[i].pos[k].y=(i+1)*espacement_vert_g;
                res[i].pos[k].x=(taille_plateau/4)+(taille_serpent/2)-k;
                res[i].dir[0]=right;
                }
            else{
                res[i].pos[k].y=(i+1)*espacement_vert_d;
                res[i].pos[k].x=(3*taille_plateau/4)+(taille_serpent/2)+k;
                res[i].dir[0]=left;
                }
            }
        }
    return res;
    }






int main(){
    snake Snake=init_snake(2,joueur);
    Snake.pos[0].x=10;
    Snake.pos[1].x=11;
    Snake.pos[0].y=10;
    Snake.pos[1].y=10;
    plateau p=init_plateau(30);
    snake* snakes=init_snakes(2,p.taille);
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
    int continuer =1;
    int selecteur=1;
    printf("Position texte 1 x: %d y:%d\n",positionTexte1.x,positionTexte1.y);
    printf("Dimensions texte 1 w: %d h: %d\n",texte->w,texte->h);
    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer=0;
                break;
            case SDL_MOUSEBUTTONUP:
                if((event.button.button==SDL_BUTTON_LEFT) && (selecteur==0) && (event.button.x>positionTexte1.x) && (event.button.x<positionTexte1.x+texte->w) && (event.button.y<positionTexte1.y) && (event.button.y>positionTexte1.y+texte->h)){
                selecteur=1;

                }
                printf("%d %d\n",event.button.x,event.button.y);
                printf("Selecteur : %d\n",selecteur);
                break;
            default:
                break;
            }

           /* else if(selecteur==0 && positionMouse.x>positionTexte2.x && positionMouse.x<positionTexte2.x+texte2->w && positionMouse.y<positionTexte2.y && positionMouse.y>positionTexte2.y+texte2->h){
                selecteur=2;}*/
            switch(selecteur){
                case 0:
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte1);
                    SDL_BlitSurface(texte2,NULL,ecran,&positionTexte2);
                    break;
                case 1:
                    jeu_sdl(ecran,&Snake,1,p);
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
    return 0;}
