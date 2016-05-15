/** Gestion des Bonus
 * */
coord avoirCoordonneesLibreHasard(plateau plat);

void ajoutFruit(coord cor, plateau* plat);

void ajoutPoison(coord cor,plateau* plat);

void creationTroudever(plateau* p);

void ajoutTeleporter(coord cor, plateau *plat);

void retirerBonus(coord cor, plateau *plat);

void placerFruit(plateau *plat);

bool detectionFruit(coord c,plateau plat);

void utiliserTeleporter(plateau* p ,snake* s,direction dSerpent);

void fruit_strategie(plateau* p,snake *s,coord caseFruit,direction dserpent);
