#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdbool.h>

plateau init_plateau(int n);
void movesnake(snake s,direction dir);
bools wall_hit(plateau p, snake* s,int n);
bools body_hit_aux(snake s1, snake s2);
bools body_hit(snake* s, int n);
bools collisions(plateau p,snake* s,int n);
void win(bools bs,snake s);
bools jouer(snake* s,int n, plateau p);

#endif // JEU_H_INCLUDED
