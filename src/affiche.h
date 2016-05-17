/**
 * \file affiche.h
 * \brief Header contenant les prototypes des fonctions implementees dans affiche.c

 */


#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
/**
 * \brief check Fonction cherchant si un tableau de booleen contient une valeur true
 * \param un tableau de booleens
 * \param n la taille du tableau
 * \return true si le tableau contient au moins une valeur true, false sinon
 */

bool check(bool* b, int n);

/**
 * \brief cherche_snake fonction dont l'objectif est de determiner si le corps d'un serpent (et pas sa tete) se situe sur la case de coordonnees i,j
 * \param i un entier correspondant a l'absisse d'une coordonnee
 * \param j un entier correspondant a l'ordonnee d'une coordonnee
 * \param s les serpents
 * \param n le nombre de serpents
 * \return Un tableau de booleens de taille n
 */

bool* cherche_snake(int i, int j, snake* s, int n);

/**
 * \brief cherche_tete fonction dont l'objectif est de determiner si la tete d'un serpent se situe sur la case de coordonnees i,j
 * \param i un entier correspondant a l'absisse d'une coordonnee
 * \param j un entier correspondant a l'ordonnee d'une coordonnee
 * \param s les serpents
 * \param n le nombre de serpents
 * \return Un tableau de booleens de taille n
 */

bool* cherche_tete(int i,int j, snake* s, int n);

/**
 * \brief affiche Permet d'afficher le plateau et les serpents à un instant donne
 * \param s les serpents
 * \param n le nombre de serpents
 * \return void
 */

void affiche(plateau p, snake* s,int n);

/**
 * \brief init_tab_couleur fonction stockant dans une variable globale les differentes couleurs utilisees pour l affichage
 * \return le tableau contenant les couleurs
 */

void init_tab_couleur();

/**
 * \brief init_sprites fonction stockant dans une variable globale les differentes images utilisees pour l affichage
 * \return void
 */


void init_sprites();

/**
 * \brief affiche_sdl Permet d'afficher le plateau et les serpents à un instant donne
 * \param screen fenetre de jeu
 * \param s les serpents en jeu
 * \param nbs le nombre de serpents en jeu
 * \param p le plateau de jeu
 * \param temps_debut temps entre le lancement du programme et le debut de la partie actuelle
 * \param difficulte vitesse de deplacement des serpents
 * \return void
 */

void affiche_sdl(SDL_Surface* screen, snake* s, int nbs, plateau p,int temps_debut, int difficulte);

/**
 * \brief score_snakes_sdl Permet d'affiche les scores de tous les serpents en jeu a un instant donne
 * \param screen fenetre de jeu
 * \param s les serpents en jeu
 * \param nb_ser le nombre de serpents en jeu
 * \param p le plateau de jeu
 * \param temps_debut temps entre le lancement du programme et le debut de la partie actuelle
 * \param difficulte vitesse de deplacement des serpents
 * \param taille_px nombre de pixels representant une case d un plateau
 * \param position_scoreboard endroit où on doit afficher le score
 * \return void
 */

void score_snakes_sdl(SDL_Surface* screen, snake* s, int nb_ser, plateau p,int tps_debut,int difficulte, int taille_px, SDL_Rect position_scoreboard);

/**
 * \brief load_menu_sdl Affiche le menu du jeu
 * \param screen fenetre de jeu
 * \return void
 */

void load_menu_sdl(SDL_Surface* screen);

/**
 * \brief load_options_sdl Permet d'afficher les options de jeu
 * \param screen fenetre de jeu
 * \param snakes les serpents en jeu
 * \param p le plateau de jeu
 * \param difficulte vitesse des serpents (plus difficulte est grand plus les serpents vont vite)
 * \param nbs nombre de serpents
 * \param touche Touche du clavier recuperee par le programme pour se deplacer dans les options
 * \param selecteur_position variable globale definie dans le main permettant de se deplacer dans ce dernier
 * \param continuer variable globale definie dans le main permettant de se deplacer dans ce dernier
 * \param selecteur_menu variable globale definie dans le main permettant de se deplacer dans ce dernier
 * \return un entier indiquant dans quel champ on se trouve dans les options
 */

int load_options_sdl(SDL_Surface* screen, snake* snakes, plateau p, int* difficulte, int* nbs,SDLKey touche,int selecteur_position,int* continuer, int* selecteur_menu);


/**
 * \brief load_pause_sdl Fonction permettant de mettre le jeu en pause
 * \param screen fenetre de jeu
 * \param taille_cases_px nombre de pixels representant une case d un plateau
 * \param temps_debut temps entre le lancement du programme et le debut de la partie actuelle
 * \param continuer variable globale definie dans le main permettant de se deplacer dans ce dernier
 * \return un entier servant a modifier une variable definie dans le main. Si cet entier vaut 1, alors le joueur reprend sa partie, si il vaut 0, alors il revient au menu
 */

int load_pause_sdl(SDL_Surface* screen, int taille_cases_px, int* temps_debut, int* continuer);

/**
 * \brief fin_partie_sdl Fonction demandant au joueur si il souhaite retouner au menu ou rejouer une fois sa partie terminee
 * \param screen fenetre de jeu
 * \param resultat_partie variable permettant de determiner si le joueur a perdu ou gagne
 * \param snakes les serpents en jeu
 * \param nbs le nombre de serpents
 * \param p le plateau de jeu
 * \param temps_debut temps entre le lancement du programme et le debut de la partie actuelle
 * \param difficulte vitesse des serpents
 * \param continuer variable globale definie dans le main permettant de se deplacer dans ce dernier
 * \return un entier servant a modifier une variable definie dans le main. Si cet entier vaut 1, alors le joueur recommence une partie et si il vaut 0, il retourne au menu
 */


int fin_partie_sdl(SDL_Surface* screen, bools resultat_partie, snake* snakes,int nbs, plateau p,int temps_debut,int difficulte,int* continuer);

#endif // AFFICHAGE_H_INCLUDED
