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


/**
 * @brief choix_strategie Fonction permettant de choisir la direction du serpent selon sa strategie mise en place
 * @param cible le serpent à derterminer la direction
 * @param snakes lensemble des serpents
 * @param p le plateau de jeu
 * @param toucheJoueur la touche presse par le joueur pendant le debut du tour
 * @return la direction choisi par la strategie
 */
direction choix_strategie(snake cible,snake* snakes,int nombreSerpent, plateau p,direction toucheJoueur);

bool estOccupe(coord c ,snake * snakes ,int nombreSerpent, plateau p);

bool estInverse(direction dir1,direction dir2);

direction joueur_strat(snake cible,direction toucheJoueur);

coord convertDirectionToCoord(direction dir);

direction tournerAntiHoraire(direction dir);

direction idle_strat(snake cible, snake* snakes,int nombreSerpent, plateau p);





#endif // SNAKE_H_INCLUDED
