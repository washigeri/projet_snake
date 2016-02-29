#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdbool.h>
plateau init_plateau(int n);
bool cherche_snake(int i, int j, snake s);
void affiche(plateau p, snake s);
void movesnake(snake* s,direction dir);
bool wall_hit(plateau p, snake s);
bool jouer(snake s,plateau p);

#endif // JEU_H_INCLUDED
