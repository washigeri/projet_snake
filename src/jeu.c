
/**
 * \file jeu.c
 * \brief Ce source contient l'implémentation des fonctions gérant les fonctions prncipales du jeu
 * \details Les fonctions dans ce fichier permettent notamment la création du plateau de jeu, la détection des entrées utilisateurs
 et le déplacement des serpents. Ce fichier implémente aussi les deux types d'IA: idle et défensive.

 */
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "struct.h"
#include "snake.h"
#include "affiche.h"
#include "collision.h"
#include "strategie.h"
#include "fruit.h"


#define PAS_TEMPS 100000
#define MAX_NB_SNAKE 8
/**
 *
 * \brief init_plateau Permet la creation d un tableau de n * n cases
 * \param n taille des lignes et colonnes
 * \return le plateau forme
 */

plateau* init_plateau(int n){
    plateau* res = malloc(sizeof(plateau));
    res->troudever=0;
    res->cases=(int**)calloc(n,sizeof(int*));
    int i;
    for(i=0;i<n;i++){
        res->cases[i]=(int*)calloc(n,sizeof(int));
    }
    for(i=0;i<n;i++){
        res->cases[i][0]=1;
        res->cases[i][n-1]=1;
        res->cases[0][i]=1;
        res->cases[n-1][i]=1;
    }
    res->taille=n;
    res->nombreItem=0;
    res->nombreTroudever=0;
    return res;
}

/**
 * \brief erase_plateau Permet d effacer un plateau de jeu
 * \param platAEffacer le plateau a effacer
 */
void erase_plateau(plateau* platAEffacer)
{
    int i;
    for(i = 0; i < platAEffacer->taille ;i++)
    {
        free(platAEffacer->cases[i]);
    }
    free(platAEffacer->cases);


    if(platAEffacer->troudever)
    {
        free(platAEffacer->troudever);
    }
    /*free(platAEffacer);*/

}
/**
 * \brief effacerPartie Permet d'effacer la partie de la memoire (serpent et plateau)
 * \param plat le plateau de jeu
 * \param tabSerpent la table des serpents
 * \param nombreSerpent le nombre de serpent
 */
void effacer_Partie(plateau* plat,snake* tabSerpent,int nombreSerpent)
{
    int i;
    for(i = 0 ; i < nombreSerpent;i++)
    {
        delete_snake(tabSerpent + i);
    }
    free(tabSerpent);

    erase_plateau(plat);
    free(plat);


}






bool arrete_partie(snake* s,int n){
    bool res=false;
    for(int i=1;i<n && !res;i++)
    {
        if(!s[i].dead[0])
        {
            res=true;
        }
    }
    return res;
}

/**
 * \brief win Permet de test si le joueur humain a gagne ou perdu
 * \param bs les resultat des test de collision
 * \param s le serpent a test (toujours le joueur)
 * \return true si il n'y a pas eu de collision, false sinon
 */
bools win(bools* bs,snake* s,int n){
    bools res;
    res.b=true;
    if(!bs[0].b){
    	s[0].dead[0]=true;
        res.b=false;
        res.s=s[0];
    }
    else {
        int i;
        for(i=1;i<n;i++){
            if(!bs[i].b){
                kill_snake(s[i]);
                res.s=s[i];
    	    }
        }
        res.b=arrete_partie(s,n);
    }
    free(bs);
    return res;
}
/**
 * \brief kbhit operation permet de preparer la console a lappui sur une touche
 * \return le succes ou non de l'operation
 */

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf=tcgetattr(STDIN_FILENO, &oldt);
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

void depart(snake* s,int n, plateau p){
    int i;
    char dir;
    bool debut=false;
    while(!debut){
        if(kbhit()){
            dir=getchar();
            if(dir=='z' || dir=='q' || dir=='s' || dir=='d'){
                debut=true;
            }
        }
    }
    movesnake(s[0],dir);
    for(i=1;i<n;i++){
        if(!s[i].dead[0]){
            movesnake(s[i],choix_strategie(s[i],s,n,p,0));
        }
    }
}


/**
 * \brief jouer permet de jouer un tour de jeu
 *   * faire avancer les differents serpent selon leurs differentes strategies
 *   * tester les collisions
 *   * activer ou non le fin de la partie
 * \param s la liste des serpents
 * \param n le nombre de serpent
 * \param p le plateau de jeu
 * \return la collision provoque dans le tour
 */
bools* jouer(snake* s,int n,plateau* p){
    int i;
    char dir='n';
    if(kbhit()){
        dir=getchar();
    }

    if(!(dir=='z' || dir=='q' || dir=='s' || dir=='d'))
    {
        dir = *(s[0].dir);
    }


    affiche(*p,s,n);
    for(i=0;i<n;i++){
        if(!s[i].dead[0]){

            direction dirchoisi = choix_strategie(s[i],s,n,*p,dir);

            if(detectionFruit(s[i].pos[0],p))
            {
                fruit_strategie(p,s+i,s[i].pos[0],dirchoisi);

            }
            else
            {
                movesnake(s[i],dirchoisi);
            }
            /*
                //assurer la collision entre fruit :utiliser la fonction...
                if(!collisions_fruit(p,s[i],n,dirchoisi))
                {
                    movesnake(s[i],dirchoisi);
                }
                */

        }
    }
    affiche(*p,s,n);
    bools* res=collisions(*p,s,n);

    //placement dunn fruit sur le plateau
    placerFruit(p);

    usleep(PAS_TEMPS);
    return res;
}
/**
 * @brief Fonction utilisée dans les tests unitaires pour tester les collisions
 * @param s Tableau contenant tous les serpents en jeu
 * @param n Nombre de serpent en jeu
 * @param p Plateau de jeu
 * @return Tableau de bools indiquant si chaque serpent a gagné ou perdu la partie
 */
bools* jouer_test_collisions(snake* s,int n, plateau p){
    affiche(p,s,n);
    movesnake(s[0],s[0].dir[0]);
    bools* res=collisions(p,s,n);
    usleep(PAS_TEMPS);
    return res;}


bools* jouer_sdl(SDL_Surface* screen, snake* s, int nb_ser, plateau p, SDLKey touche,int difficulte,int temps_debut){
    char dir=s[0].dir[0];
    switch(touche){
        case SDLK_DOWN:
            dir=down;
            break;
        case SDLK_s:
            dir=down;
            break;
        case SDLK_UP:
            dir=up;
            break;
        case SDLK_z:
            dir=up;
            break;
        case SDLK_LEFT:
            dir=left;
            break;
        case SDLK_q:
            dir=left;
            break;
        case SDLK_RIGHT:
            dir=right;
            break;
        case SDLK_d:
            dir=right;
            break;
        default:
            break;
        }
    //affiche_sdl(screen,s,nb_ser,p);
    movesnake(s[0],choix_strategie(s[0],s,nb_ser,p,dir));
    for(int i=1;i<nb_ser;i++){
        if(!s[i].dead[0]){
            movesnake(s[i],choix_strategie(s[i],s,nb_ser,p,0));
            }
        }
    affiche_sdl(screen,s,nb_ser,p,temps_debut);
    bools* res=collisions(p,s,nb_ser);
    SDL_Delay(30/difficulte);

    return res;
}
