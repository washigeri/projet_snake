#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED




/**
 * @brief init_snake Permet la creation dun serpent dune taille definie
 * @param len taille du serpent
 * @return le serpent cree
 */
 
snake init_snake(int len,type typesnake);

/**
 * @brief test si 2 serpents sont égaux
 * @param snake
 * @param snake
 */

bool egalite_snake(snake s1, snake s2);

/**
 * @brief change_IA Permet le changement de l'intellgence artificielle d un serpent
 * @param snake
 * @param typeAI
 */
 
void change_IA(snake snake, type typeAI);



#endif // SNAKE_H_INCLUDED
