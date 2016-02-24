#ifndef __JEU_H
#define __JEU_H
#include "snake.h"


void init_tableau(int** tableau,int dim);
void appplique_partie(int** tableau,Coord* l,int longsnake);
Coord traduction_saisie(int input);
int** jouer_Tour(int input,int** tableau,int dim,Coord* l,int longsnake);

#endif
