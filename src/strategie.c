

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "struct.h"
#include "snake.h"
#include "collision.h"
#include "strategie.h"


/*Valeurs defensives*/
/* AntiBlocage, Plus le coefficient est eleve moins le serpents aura tendance a s'enrouler
 *autour de lui-meme*/
#define COEFF_TARGETSNAKE 1
/* Timidite, Plus le coefficient est haut plus le serpent evitera ses congeneres*/
#define COEFF_OTHERSNAKE 2
/* Liberte, plus le coefficient est eleve, plus le serpent voudra eloigner des murs du plateau*/
#define COEFF_PLATEAU 2
/* Prevoyance ,plus le coefficient est eleve plus le serpent se mefira de la tete des autres serpents*/
#define COEFF_HEAD 5

/* Coefficient attribuee au valeurs defensives pour IA defensive*/
#define COEFF_DEFENSIV 2

/* Coefficient attribuee au valeurs defensives pour IA offensives*/
#define COEFF_OFFENSIV 1

/*Valeurs offensives*/

/*Aggresivite, attirance pour les tetes des serpents*/
#define PDS_MAX_ATTIRANCE_HEAD 1000

/*Bonus strategie, Le bonus gagne lorsque que le serpent fait un coup strategique*/
#define PDS_BONUS_COUP_STRATEGIQ 1500

/*Application strategie, a quel distance le serpent doit etre au minimun pour appliquer des coups strategique*/
#define DISTANCE_MAX_APPLICATION_STRATEG 5





/**
 * \brief joueur_strat Fonction de traitement de la strategie du joueur
 *  *Se contente de choisir la direction selectionner par le joueur
 *  *Si la direction est linverse de la direction generale il continu tout droit
 * \param cible le serpent a determiner la direction
 * \param toucheJoueur la direction choisi par le joueur
 * \return la direction apres analyse
 */
direction joueur_strat(snake cible,direction toucheJoueur)
{
    if(estInverse(*(cible.dir),toucheJoueur))
    {
        return *(cible.dir);
    }
    else
    {
        return toucheJoueur;
    }

}


/**
 * \brief tournerAntiHoraire permet de selectionner une direction qui se trouve a gauche de la direction en parametre
 *
 * \param dir la direction
 * \return la direction a gauche
 */
direction tournerAntiHoraire(direction dir)
{

    if(dir == left)
    {
        return down;
    }
    else if(dir == right)
    {

        return up;
    }
    else if(dir == up)
    {
        return left;
    }

    return right;


}


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
direction idle_strat(snake cible, snake* snakes,int nombreSerpent, plateau p){


    direction res = (*(cible.dir));

    direction old =res;

    int testmax = 0;
    coord dirSouhaite,dirFutur;

    dirFutur = convertDirectionToCoord(res);

    dirSouhaite.x = cible.pos->x + dirFutur.x;
    dirSouhaite.y = cible.pos->y + dirFutur.y;

    //On test si le serpent peut aller autre part (si ou bout de 3 test le test echoue le serpent se suicide)
    while(testmax < 5 && estOccupe(dirSouhaite,snakes,nombreSerpent,p))
    {

        /*TODO:Et si le serpent a une taille de 1 ?*/
        res =tournerAntiHoraire(res);
        //Test si
        if(!estInverse(res,old))
        {
            dirFutur = convertDirectionToCoord(res);
            dirSouhaite.x = cible.pos->x + dirFutur.x;
            dirSouhaite.y = cible.pos->y + dirFutur.y;
        }
        testmax++;
    }

    return res;

}



/**
 * \brief calculDistanceTaxicab Permet de calculer la distance entre deux coordonnees selon la methode du TaxiCab
 * ( ou de Manhattan)
 *
 * \param cor1 la coordonnee 1
 * \param cor2 la coordonnee 2
 * \return la distance de Manhattan entre les deux cordonnees
 */
unsigned int calculDistanceTaxicab(coord cor1,coord cor2)
{

    unsigned int res = 0;

    /*x*/
    res = abs((cor1.x - cor2.x));
    /*y*/
    res += abs((cor1.y -cor2.y));


    return res;

}

/**
 * \brief calculPoidsTableau permet de calculer l influence des murs du plateaux sur une coordonnees donnees
 * Plus la case est eloigne des murs du tableau plus le poids est eleve
 * \note COEFF_PLATEAU est le coefficient de multiplication du poids
 * \param cor la coordonnee
 * \param p le plateau de jeu
 * \return le poids de la case par rapport a l'influence du plateau
 */
unsigned int calculPoidsTableau(coord cor,plateau p)
{
    unsigned int res;

    coord cort;
    cort.x = p.taille/2;
    cort.y = p.taille/2;

    res = p.taille - calculDistanceTaxicab(cor,cort);

    return res * COEFF_PLATEAU;
}


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
unsigned int calculPoidsSerpent(coord pos,snake cible,snake * snakes,int nombreSerpent,plateau p)
{
    unsigned int res = 0;

    bool esttete;
    int i,j;

    for(i = 0 ; i < nombreSerpent;i++)
    {
        unsigned int poidstotalserpent = 0;

        if(egalite_snake(snakes[i],cible))
        {
            for(j = 0; j < snakes[i].taille ; j++)
            {
                poidstotalserpent += calculDistanceTaxicab(snakes[i].pos[j],pos) * COEFF_TARGETSNAKE;
            }

        }
        else
        {
            for(j = 0; j < snakes[i].taille ; j++)
            {
                if(!snakes[i].dead[0]){
                esttete = (j==0);



                poidstotalserpent += calculDistanceTaxicab(snakes[i].pos[j],pos) * COEFF_OTHERSNAKE * (1 + esttete*COEFF_HEAD);
            }
            }
        }

        res += poidstotalserpent/snakes[i].taille;
    }

    res /= nombreSerpent;


    return res;
}

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
direction defensiv_strat(snake cible,snake* snakes,int nombreSerpent,plateau p)
{
    int poids = -1;
    direction actuel = *cible.dir;
    direction res = *cible.dir;
    coord coor;

    int i;
    for(i = 0; i < 4 ; i++)
    {

        coor.x = convertDirectionToCoord(actuel).x + cible.pos->x;
        coor.y = convertDirectionToCoord(actuel).y + cible.pos->y;


        if(!estOccupe(coor,snakes,nombreSerpent,p))
        {
            int poidscurrent = 0;
            poidscurrent += calculPoidsTableau(coor,p) *COEFF_DEFENSIV;
            poidscurrent += calculPoidsSerpent(coor,cible,snakes,nombreSerpent,p) * COEFF_DEFENSIV;


            if(poids <= poidscurrent)
            {
                poids = poidscurrent;
                res = actuel;

            }

        }

        actuel = tournerAntiHoraire(actuel);
    }

    /*printf("calcul:%d\n",poids);*/

    return res;
}
/**
 * @brief calculPoidsTete permet de calculer poids de la case a partir des tete des tetes des adversaires
 * @param coor la case teste
 * @param cible le serpents cible
 * @param snakes la listes des serpents
 * @param nombreSerpent le nombre de serpent
 * @return le poids attribue
 */
int  calculPoidsTete(coord coor,snake cible,snake*snakes,int nombreSerpent)
{
    int res = 0;
    int i;
    for(i = 0; i<nombreSerpent;i++)
    {
        if(!egalite_snake(cible,snakes[i]) && !snakes[i].dead[0])
        {
            res = PDS_MAX_ATTIRANCE_HEAD / (calculDistanceTaxicab(snakes[i].pos[0],coor)+1);

        }
    }

    return res;

}
/**
 * @brief connaitreSnakeLePlusProche permet de connaitre le serpent ennemie le plus proche la cible
 * @param cible le serpent cible
 * @param snakes la listes des serpents
 * @param nombreSerpent le nombre de serpent
 * @return le snake le plus proche
 */

snake connaitreSnakeLePlusProche(snake cible,snake*snakes,int nombreSerpent)
{
    snake res;
    int distance = -1;
    int i;

    for(i=0;i<nombreSerpent;i++)
    {
        if(!egalite_snake(cible,snakes[i]) && !snakes[i].dead[0])
        {
            if(distance>calculDistanceTaxicab(snakes[i].pos[0],cible.pos[0]) || distance == -1)
            {
                distance = calculDistanceTaxicab(snakes[i].pos[0],cible.pos[0]) ;
                res = snakes[i];
            }

        }

    }

    return res;

}


/**
 * @brief calculdirection permet de calculer la direction  du vecteur a partir de deux points de l origin a extremite
 * @param origin coord d'origine
 * @param exter coord de destination
 * @return la direction du vecteur
 */
direction calculdirection(coord origin,coord exter)
{
    direction res =up;
    if(origin.y<exter.y)
    {
        if(exter.y-origin.y > abs(exter.x-origin.x))
        {
            res=up;
        }
        else if (exter.x>origin.x)
        {
            res = left;
        }
        else
        {
            res = right;
        }
    }
    else
    {
        if(origin.y-exter.y > abs(exter.x-origin.x))
        {
            res=down;
        }
        else if (exter.x>origin.x)
        {
            res = left;
        }
        else
        {
            res = right;
        }

    }

    return res;

}
/**
 * @brief calculStrategie analyse les cas de positionnement de l'adversaire et de cible et juge si un coup a une importance strategie ou non
 * @param cible le serpent cible
 * @param directiontest la direction teste
 * @param snakeProche le serpent ennemi
 * @return le bonus attribue nul ou egal a PDS_BONUS_COUP_STRATEGIQ
 */
int calculStrategie(snake cible, direction directiontest, snake snakeProche)
{
    int res = 0;
    direction dirsnake;
    dirsnake = calculdirection(cible.pos[0],snakeProche.pos[0]);


    /*Cas speciaux le serpent nest pas assez proche de sa victime*/
    if(calculDistanceTaxicab(cible.pos[0],snakeProche.pos[0]) > DISTANCE_MAX_APPLICATION_STRATEG)
    {
        /*cas special
         *
         * rapprochement frontale
         *
         *     +++++  <-0000
         *
         *
         *
         * + ennemi
         * O cible
         * <- | direction
         */
        if(estInverse(dirsnake,directiontest ))
        {
            res = PDS_BONUS_COUP_STRATEGIQ;

        }

        /*cas special 2
         *
         *  croisement
         *
         *     +++++
         *              |
         *              0
         *              0
         *              0
         * + ennemi
         * O cible
         * <- | direction
         */
        else if(tournerAntiHoraire(dirsnake) == directiontest || dirsnake == tournerAntiHoraire(directiontest) )
        {
            res =PDS_BONUS_COUP_STRATEGIQ;

        }


        return res;
    }




    /*cas 1
     *
     * coupage de la route
     *              0
     *              0
     *              0
     *      ++++++  |
     *
     * + ennemi
     * O cible
     * | direction
     *
     */

    if(estInverse(dirsnake,*snakeProche.dir) && (directiontest == tournerAntiHoraire(dirsnake)
                                                 || directiontest == tournerAntiHoraire(*snakeProche.dir) ))
    {
        res = PDS_BONUS_COUP_STRATEGIQ;
    }

    /*cas 2
     *
     * encerclement
     *         000
     *     +++++ 0
     *        <-00
     *
     *
     * + ennemi
     * O cible
     * <- direction
     */


    else if(estInverse(*snakeProche.dir,directiontest) && (dirsnake == tournerAntiHoraire(directiontest)
                                                           || dirsnake == tournerAntiHoraire(*snakeProche.dir) ))
    {
        res = PDS_BONUS_COUP_STRATEGIQ;
    }

    /*cas 3
     *
     * queue de poisson (debauche sur l'encerclement)
     *         0000
     *     +++++  |
     *
     *
     *
     * + ennemi
     * O cible
     * <- direction
     */
    else if(*cible.dir == *snakeProche.dir && estInverse(dirsnake,directiontest))
    {
        res = PDS_BONUS_COUP_STRATEGIQ;
    }
    return res;

}




/**
 * @brief offensive_strat la gestion de la strategie offensive
 * *Les coefficients des constantes defensives sont reduites par rapport a la strategie defensive
 * *Le serpent est attirees par les tetes de ces adversaires
 * *Le serpent connait des coups strategiques a appliquer
 * @param cible le serpent cible
 * @param snakes la liste des serpents
 * @param nombreSerpent le nombre de serpent
 * @param p le plateau de jeu
 * @return la direction adoptee par le serpent
 */
direction offensive_strat(snake cible,snake* snakes,int nombreSerpent,plateau p)
{
    int poids = -1;
    direction actuel = *cible.dir;
    direction res = *cible.dir;
    coord coor;

    int i;
    for(i = 0; i < 4 ; i++)
    {

        coor.x = convertDirectionToCoord(actuel).x + cible.pos->x;
        coor.y = convertDirectionToCoord(actuel).y + cible.pos->y;


        if(!estOccupe(coor,snakes,nombreSerpent,p))
        {
            int poidscurrent = 0;
            poidscurrent += calculPoidsTableau(coor,p) *COEFF_OFFENSIV;
            poidscurrent += calculPoidsSerpent(coor,cible,snakes,nombreSerpent,p) *COEFF_OFFENSIV;
            poidscurrent += calculPoidsTete(coor,cible,snakes,nombreSerpent);
            poidscurrent += calculStrategie(cible,actuel,connaitreSnakeLePlusProche(cible,snakes,nombreSerpent));


            if(poids < poidscurrent)
            {
                poids = poidscurrent;
                res = actuel;

            }

        }

        actuel = tournerAntiHoraire(actuel);
    }


    return res;
}

/**
         * \brief choix_strategie Fonction permettant de choisir la direction du serpent selon sa strategie mise en place
         * \param cible le serpent à derterminer la direction
         * \param snakes lensemble des serpents
         * \param p le plateau de jeu
         * \param toucheJoueur la touche presse par le joueur pendant le debut du tour
         * \return la direction choisi par la strategie
         */
direction choix_strategie(snake cible,snake* snakes,int nombreSerpent, plateau p,direction toucheJoueur){
    switch(cible.playType)
    {

    case joueur :
        return toucheJoueur;
        break;
    case idle :
        return idle_strat(cible,snakes,nombreSerpent,p);
        break;
    case defensif :
        return defensiv_strat(cible,snakes,nombreSerpent,p);
        break;
    case offensif :
        return offensive_strat(cible,snakes,nombreSerpent,p);
        break;
    default :
        return toucheJoueur;
        break;
    }
}
