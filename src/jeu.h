#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdbool.h>




/**
 *
 * @brief init_plateau Permet la creation d un tableau de n * n cases
 * @param n taille des lignes et colonnes
 * @return le plateau forme
 */
plateau init_plateau(int n);
/**
 * @brief movesnake Procedure de mise à jour et de deplacement du serpent dans
 * une direction donne
 * @param s le serpent a deplacer
 * @param dir la direction souhaitee
 */
void movesnake(snake s,direction dir);

bools* init_bools_tab(int n);
/**
 * @brief wall_hit Permet de tester si le serpent touche un mur du plateau
 * @param p le plateau de jeu
 * @param s les differents serpents du jeu
 * @param n le nombre de serpents
 * @return la cas de collision avec un mur
 */
bools* wall_hit(plateau p, snake* s,int n);
/**
 * @brief body_hit_aux Permet de tester le cas de collision entre deux serpents
 * @param s1 serpent 1
 * @param s2 serpent 2
 * @return le cas de collision
 */
bools body_hit_aux(snake s1, snake s2);
/**
 * @brief body_hit Permet de tester les collisions de tous les serpents entre eux
 * @param s le tableau de serpent
 * @param n le nombre de serpent
 * @return le cas de collision entre serpents
 */

/*TODO :faire en sorte denvoyer une liste de collision et non un element unique (bools*)*/
bools* body_hit(snake* s,int n);
/**
 * @brief collisions Permet de occuper de tout les sorte de collisions entre le
 * plateau et les sepents
 * @param p le plateau forme
 * @param s la liste de serpent du jeu
 * @param n le nombre de serpent
 * @return le cas de collision
 */
/*TODO :faire en sorte denvoyer une liste de collision et non un element unique (bools*)*/
bools* collisions(plateau p,snake* s,int n);
/**
 * @brief win Permet de test si le joueur humain a gagne ou perdu
 * TODO NOTE : cette commande ne permet qu un jeu a un joueur et un ordinateur pour
 * instant
 * @param bs les resultat des test de collision
 * @param s le serpent a test (toujours le joueur)
 * @return true si il n'y a pas eu de collision, false sinon
 */

bool win(bools* bs,snake* s,int n);

/**
 * @brief kbhit operation permet de preparer la console a lappui sur une touche
 * @return le succees ou non de l operation
 */
int kbhit();
/**
 * @brief jouer permet de jouer un tour de jeu
 *   * faire avancer les differents serpent selon leurs differentes strategies
 *   * tester les collisions
 *   * activer ou non le fin de la partie
 * @param s la liste des serpents
 * @param n le nombre de serpent
 * @param p le plateau de jeu
 * @return la collision provoque dans le tour
 */
/*TODO :faire en sorte denvoyer une liste de collision et non un element unique (bools*)*/
bools* jouer(snake* s,int n,plateau p);

#endif // JEU_H_INCLUDED
