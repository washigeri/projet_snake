
/**
 * \file jeu.c
 * \brief Ce source contient l'implémentation des fonctions gérant les fonctions prncipales du jeu
 * \details Les fonctions dans ce fichier permettent notamment la création du plateau de jeu, la détection des entrées utilisateurs
 et le déplacement des serpents. Ce fichier implémente aussi les deux types d'IA: idle et défensive.

 */

#include <stdio.h>
#include <stdio_ext.h>
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

#define MAX_NB_SNAKE 10


/**
 *
 * \brief init_plateau Permet la creation d un tableau de n * n cases
 * \param n taille des lignes et colonnes
 * \return le plateau forme
 */

plateau init_plateau(int n){
    plateau res;
    res.cases=(int**)calloc(n,sizeof(int*));
    int i;
    for(i=0;i<n;i++){
        res.cases[i]=(int*)calloc(n,sizeof(int));
    }
    for(i=0;i<n;i++){
    	res.cases[i][0]=1;
    	res.cases[i][n-1]=1;
    	res.cases[0][i]=1;
    	res.cases[n-1][i]=1;
    }
    res.taille=n;
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


}

/**
 * \brief movesnake Procedure de mise à jour et de deplacement du serpent dans
 * une direction donne
 * \param s le serpent a deplacer
 * \param dir la direction souhaitee
 */
void movesnake(snake s,direction dir){
    if(!estInverse(s.dir[0],dir)){
        int i;
        switch (dir){
        case right:
                for(i=s.taille-1;i>0;i--){
                    s.pos[i].x=s.pos[i-1].x;
                    s.pos[i].y=s.pos[i-1].y;
                }
                s.pos[0].x++;
                s.dir[0]=dir;
                break;
        case left:
                for(i=s.taille-1;i>0;i--){
                    s.pos[i].x=s.pos[i-1].x;
                    s.pos[i].y=s.pos[i-1].y;
                }
                s.pos[0].x--;
                s.dir[0]=dir;
                break;
        case up:
                for(i=s.taille-1;i>0;i--){
                    s.pos[i].x=s.pos[i-1].x;
                    s.pos[i].y=s.pos[i-1].y;
                }
                s.pos[0].y--;
                s.dir[0]=dir;
                break;
        case down:
                for(i=s.taille-1;i>0;i--){
                    s.pos[i].x=s.pos[i-1].x;
                    s.pos[i].y=s.pos[i-1].y;
                }
                s.pos[0].y++;
                s.dir[0]=dir;
                break;
        }
    }
    else {
    	movesnake(s,s.dir[0]);
    }
}

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
  res.b=true;
  res.s=s1;
  if(!s1.dead[0] && !s2.dead[0]){
      if(!egalite_snake(s1,s2)){
          int k=0;
          while(k<s2.taille && res.b){
              if(s1.pos[0].x==s2.pos[k].x && s1.pos[0].y==s2.pos[k].y){
                  res.b=false;
              }
              k++;
          }
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
bool win(bools* bs,snake* s,int n){
    bool res=true;
    if(!bs[0].b){
    	s[0].dead[0]=true;
        printf("G A M E O V E R\n\n");
        res=false;
    }
    else {
        int i;
        for(i=1;i<n;i++){
            if(!bs[i].b){
                kill_snake(s[i]);
    	    }
        }
        res=arrete_partie(s,n);
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
bools* jouer(snake* s,int n,plateau p){
    int i;
    char dir=s[0].dir[0];
    if(kbhit()){
    	dir=getchar();
    }
    if(dir=='z' || dir=='q' || dir=='s' || dir=='d'){
        affiche(p,s,n);
        movesnake(s[0],choix_strategie(s[0],s,n,p,dir));
        for(i=1;i<n;i++){
            if(!s[i].dead[0]){
    	        movesnake(s[i],choix_strategie(s[i],s,n,p,0));
    	    }
        }
        affiche(p,s,n);
    }
    else {
    	affiche(p,s,n);
    	movesnake(s[0],s[0].dir[0]);
    	for(i=1;i<n;i++){
    	    if(!s[i].dead[0]){
    	        movesnake(s[i],choix_strategie(s[i],s,n,p,0));
    	    }
    	}
    	affiche(p,s,n);
    }
    bools* res=collisions(p,s,n);
    usleep(100000);
    return res;
}

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
    SDL_Delay(difficulte*70);
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
    usleep(100000);
    return res;
}









