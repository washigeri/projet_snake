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


/**
 * @brief estOccupe Permet de savoir si une case est occupe par un serpent ou un obstacle
 * @param c la coordonnes de la case
 * @param snakes le tableau de serpent
 * @param nombreSerpent le nombre de serpent
 * @param p le plateau
 * @return vrai si occupe
 */
bool estOccupe(coord c ,snake * snakes ,int nombreSerpent, plateau p);
/**
 * @brief estInverse Permet de savoir si deux coordonnees sont inversees utile pour savoir si le
 * serpent ne fais pas marche arriere
 * @param dir1
 * @param dir2
 * @return vrai si lezs cordonnees sont inversees
 */
bool estInverse(direction dir1,direction dir2);
/**
 * @brief joueur_strat Fonction de traitement de la strategie du joueur
 *  *Se contente de choisir la direction selectionner par le joueur
 *  *Si la direction est linverse de la direction generale il continu tout droit
 * @param cible le serpent a determiner la direction
 * @param toucheJoueur la direction choisi par le joueur
 * @return la direction apres analyse
 */
direction joueur_strat(snake cible,direction toucheJoueur);
/**
 * @brief convertDirectionToCoord Permet de convertir une direction en coordonnees
 *Exemple "haut" devient "0,-1"
 * @param dir la direction a convertir
 * @return la coordonnee
 */
coord convertDirectionToCoord(direction dir);
/**
 * @brief tournerAntiHoraire permet de selectionner une direction qui se trouve a gauche de la direction en parametre
 *
 * @param dir la direction
 * @return la direction a gauche
 */
direction tournerAntiHoraire(direction dir);
/**
 * @brief idle_strat Fonction de traitement de la strategie AI IDLE
 * *le serpent se contente daller tout droit sauf sil rencontre un obstacle
 * *si les trois directions possibles sont occupee le serpent se suicide en allant tout droit dans lobstacle
 * @param cible le serpent a determine rla direction
 * @param snakes le tableau des serpents
 * @param nombreSerpent le nombre de serpents
 * @param p le plateau de jeu
 * @return la direction selectionne par la strategie
 */
direction idle_strat(snake cible, snake* snakes,int nombreSerpent, plateau p);





#endif // SNAKE_H_INCLUDED
