/**
 * \file struct.h
 * \brief Ce fichier d'en-tête contient les structures et types utilisés pour la conception et l'utilisation du jeu
 */


#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

/**
 * \enum direction
 * \brief Type énuméré permettant de stocker la direction de déplacement
 * 
 */

typedef enum {left='q',right='d',up='z',down='s'} direction;

/**
 * \struct coord struct.h Structures
 * \brief Structure permettant de stocker les coordonnées d'un point dans l'espace
 */


typedef struct {int x;int y;} coord;

/**
 *
 * \struct snake
 * \brief Structure permettant de créer un serpent
 * \details Cette structure contient 3 éléments : - un tableau de coord à une dimension permettant de stocker les coordonnées de chaque partie du corps du serpent
 *												  - un entier permmettant de stocker la taille du serpent
 *												  - une direction indiquant la direction actuelle du serpent, qui serau utilisée dans la programmation de l'IA
 */

typedef struct {coord* pos;
                int taille;
                direction* dir;} snake;


/**
 *
 * \struct plateau
 * \brief Structure permettant de stocker les cases d'un plateau, ainsi que sa taille
 */


typedef struct {int** cases;
                int taille;} plateau;


#endif // STRUCT_H_INCLUDED
