/**
 * \file struct.h
 * \brief Ce fichier d'en-tete contient les structures et types utilises pour la conception et l'utilisation du jeu
 */

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include<stdbool.h>
/**
 * \enum direction
 * \brief Type enumere permettant de stocker la direction de deplacement
 *
 */

typedef enum {left='q',right='d',up='z',down='s'} direction;

/**
 * \enum type
 * \brief Type enumere permettant d'indiquer la nature d'un serpent (joueur ou ia, et quel type d'ia)
 *
 */

typedef enum {joueur,idle,defensif,offensif} type ;

/**
 * \struct coord struct.h Structures
 * \brief Structure permettant de stocker les coordonnees d'un point dans l'espace
 */

typedef struct {int x;int y;} coord;

/**
 *
 * \struct snake
 * \brief Structure permettant de creer un serpent
 * \details Cette structure contient 3 elements : - un tableau de coord à une dimension permettant de stocker les coordonnees de chaque partie du corps du serpent
 *						  - un entier permmettant de stocker la taille du serpent
 *						  - une direction indiquant la direction actuelle du serpent
						  - un type indiquant le type du serpent (joueur, ia defensive ou offensive ...)
						  - un booleen indiquand si le serpent est mort ou non
 */

typedef struct {coord* pos;
                int taille;
                direction* dir;
                type playType;
                bool* dead;
                int* score;
                } snake;

/**
 *
 * \struct plateau
 * \brief Structure permettant de stocker les cases d'un plateau, ainsi que sa taille
 */

typedef struct {int** cases;
                int taille;
                int nombreItem;
                coord* troudever;
                int nombreTroudever;
               } plateau;

/**
 *
 * \struct bools
 * \brief Structure permettant de savoir si un serpent perd la partie ou la continue. Si b vaut false le serpent a perdu sinon il continue la partie.
 */

typedef struct {bool b; snake s;} bools;

#endif // STRUCT_H_INCLUDED
