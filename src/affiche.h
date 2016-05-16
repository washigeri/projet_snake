/**
 * \file affiche.h
 * \brief Header contenant les prototypes des fonctions implémentées dans affiche.c

 */


#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
/**
 * \brief check Fonction cherchant si un tableau de booléen contient une valeur true
 * \param un tableau de booléens
 * \param n la taille du tableau
 * \return true si le tableau contient au moins une valeur true, false sinon
 */

bool check(bool* b, int n);

/**
 * \brief cherche_snake fonction dont l'objectif est de déterminer si le corps d'un serpent (et pas sa tête) se situe sur la case de coordonnées i,j
 * \param i un entier correspondant a l'absisse d'une coordonnée
 * \param j un entier correspondant a l'ordonnée d'une coordonnée
 * \param s les serpents
 * \param n le nombre de serpents
 * \return Un tableau de booléens de taille n
 */

bool* cherche_snake(int i, int j, snake* s, int n);

/**
 * \brief cherche_tete fonction dont l'objectif est de déterminer si la tête d'un serpent se situe sur la case de coordonnées i,j
 * \param i un entier correspondant a l'absisse d'une coordonnée
 * \param j un entier correspondant a l'ordonnée d'une coordonnée
 * \param s les serpents
 * \param n le nombre de serpents
 * \return Un tableau de booléens de taille n
 */

bool* cherche_tete(int i,int j, snake* s, int n);

/**
 * \brief affiche Permet d'afficher le plateau et les serpents à un instant donné
 * \param s les serpents
 * \param n le nombre de serpents
 * \return void
 */

void affiche(plateau p, snake* s,int n);

int** init_tab_couleur();

void affiche_sdl(SDL_Surface* screen, snake* s, int nbs, plateau p,int temps_debut);

void score_snakes_sdl(SDL_Surface* screen,snake* s,int nb_ser, plateau p, int tps_debut,int taille_px,SDL_Rect position_scoreboard);

void load_menu_sdl(SDL_Surface* screen);

int load_options_sdl(SDL_Surface* screen, snake* snakes, plateau p, int* difficulte, int* nbs,SDLKey touche,int selecteur_position,int* continuer, int* selecteur_menu);

int load_pause(SDL_Surface* screen, int taille_cases_px, int* temps_debut);

int fin_partie_sdl(SDL_Surface* screen, bools resultat_partie, snake* snakes,int nbs, plateau p,int temps_debut);

#endif // AFFICHAGE_H_INCLUDED
