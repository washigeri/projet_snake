#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

bool check(bool* b, int n);
bool* cherche_snake(int i, int j, snake* s, int n);
bool* cherche_tete(int i,int j, snake* s, int n);
void affiche(plateau p, snake* s,int n);

#endif // AFFICHAGE_H_INCLUDED
