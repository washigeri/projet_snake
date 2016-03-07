#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdbool.h>

plateau init_plateau(int n);
void movesnake(snake s,direction dir);
bool wall_hit(plateau p, snake* s,int n);
bool head_s_hit(snake s1, snake s2);
bool body_hit(snake* s, int n);
bool jouer(snake* s,int n, plateau p);

#endif // JEU_H_INCLUDED
