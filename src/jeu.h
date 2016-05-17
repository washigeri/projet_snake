/**
 * \file jeu.h
 * \brief Ce header contient les prototypes des fonctions implementees dans jeu.c.

 */

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>




/**
 *
 * \brief init_plateau Permet la creation d un tableau de n * n cases
 * \param n taille des lignes et colonnes
 * \return le plateau forme
 */
plateau* init_plateau(int n);
/**
 * \brief erase_plateau Permet d effacer un plateau de jeu
 * \param platAEffacer le plateau a effacer
 */
void erase_plateau(plateau* platAEffacer);

/**
 * \brief effacerPartie Permet d'effacer la partie de la memoire (serpent et plateau)
 * \param plat le plateau de jeu
 * \param tabSerpent la table des serpents
 * \param nombreSerpent le nombre de serpent
 */
void effacer_Partie(plateau* plat,snake* tabSerpent,int nombreSerpent);


/**
 * @brief arrete_partie permet darrete la partie quand tous les serpent sont mort
 * @param s la liste des serpent
 * @param n la nombre de serpent
 * @return
 */
bool arrete_partie(snake* s,int n);

/**
 * \brief win Permet de test si le joueur humain a gagne ou perdu
 * \param bs les resultat des test de collision
 * \param s le serpent a test (toujours le joueur)
 * \return true si il n'y a pas eu de collision, false sinon
 */
bools win(bools* bs,snake* s,int n);

/**
 * \brief kbhit operation permet de preparer la console a lappui sur une touche
 * \return le succes ou non de l'operation
 */
int kbhit();
/**
 * @brief depart initie le depart du jeu le jeu attend que le joueur appuye sur un touche pour commencer le jeu
 * @param s la liste des serpent
 * @param n le nombre de serpent
 * @param p le plateau
 */
void depart(snake* s,int n, plateau p);
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

bools* jouer(snake* s,int n,plateau* p);

/**
 * @brief Fonction utilisee dans les tests unitaires pour tester les collisions
 * @param s Tableau contenant tous les serpents en jeu
 * @param n Nombre de serpent en jeu
 * @param p Plateau de jeu
 * @return Tableau de bools indiquant si chaque serpent a gagne ou perdu la partie
 */

bools* jouer_test_collisions(snake* s,int n, plateau p);

/**
 * @brief jouer_sdl permet de jouer un tour de jeu, deplacer les serpents en jeu selon leurs strategies ainsi que detecter les collisions serpent/serpent et serpents/murs
 * Cette fonction appelle la fonnction d'affichage GUI, affiche_sdl
 * @param screen pointeur sur une SDL_Surface, representant ici la fenetre de jeu creee par SDL_SetVideoMode
 * @param s Tableau contenant tous les serpents en jeu
 * @param p plateau de jeu
 * @param touche la touche détecté au clavier pour le deplacement du joueur
 * @param difficulte vitesse du jeu
 * @param temps_debut temps en seconde depuis le début de la partie
 * @return Tableau de bools indiquant si chaque serpent a gagne ou perdu la partie
 */



bools* jouer_sdl(SDL_Surface* screen,snake* s,int nb_ser,plateau *p,SDLKey touche,int difficulte,int temps_debut);

#endif // JEU_H_INCLUDED
