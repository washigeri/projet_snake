/**
 * \file strategie.h
 * \brief Header contenant le prototype des fonctions implémentées dans strategie.c
 */


/**
 * \brief joueur_strat Fonction de traitement de la strategie du joueur
 *  *Se contente de choisir la direction selectionner par le joueur
 *  *Si la direction est linverse de la direction generale il continu tout droit
 * \param cible le serpent a determiner la direction
 * \param toucheJoueur la direction choisi par le joueur
 * \return la direction apres analyse
 */
direction joueur_strat(snake cible,direction toucheJoueur);

/**
 * \brief tournerAntiHoraire permet de selectionner une direction qui se trouve a gauche de la direction en parametre
 *
 * \param dir la direction
 * \return la direction a gauche
 */
direction tournerAntiHoraire(direction dir);
/**
 * \brief idle_strat Fonction de traitement de la strategie AI IDLE
 * *le serpent se contente daller tout droit sauf sil rencontre un obstacle
 * *si les trois directions possibles sont occupee le serpent se suicide en allant tout droit dans lobstacle
 * \param cible le serpent a determine rla direction
 * \param snakes le tableau des serpents
 * \param nombreSerpent le nombre de serpents
 * \param p le plateau de jeu
 * \return la direction selectionne par la strategie
 */
direction idle_strat(snake cible, snake* snakes,int nombreSerpent, plateau p);

/**
 * \brief calculDistanceTaxicab Permet de calculer la distance entre deux coordonnees selon la methode du TaxiCab
 * ( ou de Manhattan)
 *
 * \param cor1 la coordonnee 1
 * \param cor2 la coordonnee 2
 * \return la distance de Manhattan entre les deux cordonnees
 */
unsigned int calculDistanceTaxicab(coord cor1,coord cor2);

/**
 * \brief calculPoidsTableau permet de calculer l influence des murs du plateaux sur une coordonnees donnees
 * Plus la case est eloigné des murs du tableau plus le poids est eleve
 * \note COEFF_PLATEAU est le coefficient de multiplication du poids
 * \param cor la coordonnee
 * \param p le plateau de jeu
 * \return le poids de la case par rapport a l'influence du plateau
 */
unsigned int calculPoidsTableau(coord cor,plateau p);

/**
 * \brief calculPoidsSerpent permet de calculer le poids d'un case par rapport a l'influence des serpent
 * Plus un serpent est eloigne de la case plus le poids qu'il attribut est eleve
 * le serpent cible est egalement pris en compte dans le calcul mais possede un coefficient different des autres serpents
 * le poids est calcule pour tous les serpents et pour tous leurs membres du corps
 *
 * \note COEFF_TARGETSNAKE le coefficient de multiplication du serpent cible
 * \note COEFF_OTHERSNAKE le coefficient de multiplication des autres serpent
 * \note COEFF_HEAD le coefficent de multiplication des tete des serpent (cible exclue)
 * \param pos la coordonnees
 * \param cible le serpent cible
 * \param snakes la liste des serpent
 * \param nombreSerpent le nombre de serpent
 * \param p le plateau de jeu
 * \return le poids calcule
 */
unsigned int calculPoidsSerpent(coord pos,snake cible,snake * snakes,int nombreSerpent,plateau p);

/**
 * \brief defensiv_strat Fonction de traitement de la strategie AI DEFENSIVE
 * *Le serpent cherche à etre le plus eloigne possible des autres serpents et notamment du joueur
 * *Le serpent cherche à s'approcher le plus possible du centre
 * *Le serpent cherche a eviter de s'enrouler sur lui-meme
 * *Le serpent calcule les poids des cases adjacents est cherche celle qui a le plus de poids
 * *Si le serpent ne trouve aucune cases adjacentes il se suicide
 * \param cible le serpent cible
 * \param snakes le tableau des snakes
 * \param nombreSerpent le nombre de serpent
 * \param p le plateau de jeu
 * \return la direction choisi par le serpent
 */
direction defensiv_strat(snake cible,snake* snakes,int nombreSerpent,plateau p);

/**
 * @brief calculPoidsTete permet de calculer poids de la case a partir des tete des tetes des adversaires
 * @param coor la case teste
 * @param cible le serpents cible
 * @param snakes la listes des serpents
 * @param nombreSerpent le nombre de serpent
 * @return le poids attribue
 */
int  calculPoidsTete(coord coor,snake cible,snake*snakes,int nombreSerpent);
/**
 * @brief connaitreSnakeLePlusProche permet de connaitre le serpent ennemie le plus proche la cible
 * @param cible le serpent cible
 * @param snakes la listes des serpents
 * @param nombreSerpent le nombre de serpent
 * @return le snake le plus proche
 */

snake connaitreSnakeLePlusProche(snake cible,snake*snakes,int nombreSerpent);


/**
 * @brief calculdirection permet de calculer la direction  du vecteur a partir de deux points de l origin a extremite
 * @param origin coord d'origine
 * @param exter coord de destination
 * @return la direction du vecteur
 */
direction calculdirection(coord origin,coord exter);
/**
 * @brief calculStrategie analyse les cas de positionnement de l'adversaire et de cible et juge si un coup a une importance strategie ou non
 * @param cible le serpent cible
 * @param directiontest la direction teste
 * @param snakeProche le serpent ennemi
 * @return le bonus attribue nul ou egal a PDS_BONUS_COUP_STRATEGIQ
 */
int calculStrategie(snake cible, direction directiontest, snake snakeProche);




/**
 * @brief offensive_strat la gestion de la strategie offensive
 * *Les coefficients des constantes defensives sont reduites par rapport a la strategie defensive
 * *Le serpent est attirées par les tetes de ces adversaires
 * *Le serpent connait des coups strategiques a appliquer
 * @param cible le serpent cible
 * @param snakes la liste des serpents
 * @param nombreSerpent le nombre de serpent
 * @param p le plateau de jeu
 * @return la direction adoptee par le serpent
 */
direction offensive_strat(snake cible,snake* snakes,int nombreSerpent,plateau p);

/**
 * \brief choix_strategie Fonction permettant de choisir la direction du serpent selon sa strategie mise en place
 * \param cible le serpent à derterminer la direction
 * \param snakes lensemble des serpents
 * \param p le plateau de jeu
 * \param toucheJoueur la touche presse par le joueur pendant le debut du tour
 * \return la direction choisi par la strategie
 */
direction choix_strategie(snake cible,snake* snakes,int nombreSerpent, plateau p,direction toucheJoueur);
