/** Gestion des Bonus
 * */

/**
 * @brief avoirCoordonneesLibreHasard Permet de trouver un coordonnees libre sur le plateau de jeu (serpents exclus)
 * @param plat le plateau de jeu
 * @return une coordonnee libre
 */
coord avoirCoordonneesLibreHasard(plateau plat);
/**
 * @brief avoirCoordonneesLibreHasardAvecMarge Permet de trouver un coordonnees libre sur le plateau de jeu avec une marge dexclusion (serpents exclus)
 * @param plat le plateau de jeu
 * @return une coordonnee libre
 */
coord avoirCoordonneesLibreHasardAvecMarge(plateau plat);


/**
 * @brief ajoutFruit permet d'ajouter un fruit sur le plateau le fruit faire grandir le serpent
 * @param cor la cordonnee du fruit
 * @param plat le plateau
 */
void ajoutFruit(coord cor,plateau* plat);
/**
 * @brief ajoutFruit permet d'ajouter un poison sur le plateau le poison reduit la taille du serpent
 * @param cor la cordonnee du poisson
 * @param plat le plateau
 */
void ajoutPoison(coord cor,plateau* plat);

/**
 * @brief creationTroudever permet la creation d'un troudever sur le plateau les trou de ver son la porte de sortie
 * dun teleporter
 * @param p le plateau
 */
void creationTroudever(plateau* p);

/**
 * @brief ajoutTeleporter ajout dun teleporter les teleporter deplace la tete du serpent sur un trou de ver
 * @param cor les coordonnees
 * @param plat le plateau
 */
void ajoutTeleporter(coord cor,plateau *plat);

/**
 * @brief retirerBonus permet d enlever un objet sur une case du plateau
 * @param cor la coordonnee
 * @param plat le plateau
 */
void retirerBonus(coord cor,plateau *plat);
/**
 * @brief placerFruit permet de placer un bonus sur le plateau
 * @param plat le plateau
 */
void placerFruit(plateau *plat);
/**
 * @brief detectionFruit permet de detecter la presence dun bonus sur une case
 * @param c la coordonnee
 * @param plat le plateau
 * @return un bonus est present?
 */
bool detectionFruit(coord c,plateau* plat);
/**
 * @brief utiliserTeleporter permet au serpent dutiliser le teleporter le serpent se teleporte sur un trou de ver le teleporter et le trou ver
 * sont ensuite detruit
 * @param p le plateau
 * @param s le serpent
 * @param dSerpent le direction du serpent
 */
void utiliserTeleporter(plateau* p ,snake* s,direction dSerpent);

/**
 * @brief fruit_strategie permet de gerer les differents cas de figure pour un serpent
 * lorsqu il atterit sur une case contenant un bonus
 * @param p le plateau
 * @param s le serpent
 * @param caseFruit la coordonnee de la case
 * @param dserpent la direction du serpent
 */
void fruit_strategie(plateau *p,snake *s,coord caseFruit,direction dserpent);
