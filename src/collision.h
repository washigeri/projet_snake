
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include "struct.h"
#include "snake.h"


bools* init_bools_tab(int n);
/**
 * \brief wall_hit Permet de tester si le serpent touche un mur du plateau
 * \param p le plateau de jeu
 * \param s les differents serpents du jeu
 * \param n le nombre de serpents
 * \return la cas de collision avec un mur
 */
bools* wall_hit(plateau p, snake* s,int n);
/**
 * \brief body_hit_aux Permet de tester le cas de collision entre deux serpents
 * \param s1 serpent 1
 * \param s2 serpent 2
 * \return le cas de collision
 */
bools body_hit_aux(snake s1, snake s2);
/**
 * \brief body_hit Permet de tester les collisions de tous les serpents entre eux
 * \param s le tableau de serpent
 * \param n le nombre de serpent
 * \return le cas de collision entre serpents
 */


bools* body_hit(snake* s,int n);
/**
 * \brief collisions Permet de occuper de tout les sorte de collisions entre le
 * plateau et les sepents
 * \param p le plateau forme
 * \param s la liste de serpent du jeu
 * \param n le nombre de serpent
 * \return le cas de collision
 */

bools* collisions(plateau p,snake* s,int n);


/**
 * \brief estOccupe Permet de savoir si une case est occupe par un serpent ou un obstacle
 * \param c la coordonnes de la case
 * \param snakes le tableau de serpent
 * \param nombreSerpent le nombre de serpent
 * \param p le plateau
 * \return vrai si occupe
 */
bool estOccupe(coord c ,snake * snakes ,int nombreSerpent, plateau p);
