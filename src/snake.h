/**
 * \file snake.h
 * \brief Header contenant le prototype des fonctions implémentées dans snake.c
 */


#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED




/**
 * \brief init_snake Permet la creation dun serpent dune taille definie
 * \param len taille du serpent
 * \return le serpent cree
 */
 
snake init_snake(int len,type typesnake);

/**
 * \brief kill_snake change la valeur du booleen dead a false
 * \param snakeAeffacer serpent a tuer
 */

void kill_snake(snake s);

/**
 * \brief delete_snake permet de detruire un snake
 * \param snakeAeffacer serpent a detruire
 */
void delete_snake(snake* snakeAeffacer);

/**
 * \brief test si 2 serpents sont égaux
 * \param snake serpent 1
 * \param snake serpent 2
 */
bool egalite_snake(snake s1, snake s2);


/**
 * \brief estInverse Permet de savoir si deux coordonnees sont inversees utile pour savoir si le
 * serpent ne fais pas marche arriere
 * \param dir1
 * \param dir2
 * \return vrai si lezs cordonnees sont inversees
 */
bool estInverse(direction dir1,direction dir2);

/**
 * \brief change_IA Permet le changement de l'intelligence artificielle d un serpent
 * \param snake le serpent
 * \param typeAI le nouveau type dAI
 */
void change_IA(snake snake, type typeAI);

/**
 * \brief convertDirectionToCoord Permet de convertir une direction en coordonnees
 *Exemple "haut" devient "0,-1"
 * \param dir la direction a convertir
 * \return la coordonnee
 */
coord convertDirectionToCoord(direction dir);

/**
 * \brief movesnake Procedure de mise à jour et de deplacement du serpent dans
 * une direction donne
 * \param s le serpent a deplacer
 * \param dir la direction souhaitee
 */
void movesnake(snake s,direction dir);

/**
 * \brief add_taille_snake Fonction qui permet d'augmenter de 1 la taille du snake
 * \param snak le serpent dont la taille doit être modifié
*/
void add_taille_snake(snake *snak,direction dir);


void remove_taille_snake(snake *snak,direction dir);


void teleport_snake(snake *snak,direction dir,coord cor);

#endif // SNAKE_H_INCLUDED
