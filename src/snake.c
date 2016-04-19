
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#include "struct.h"
#include "jeu.h"
#include "snake.h"
/* AntiBlocage, Plus le coefficient est eleve moins le serpents aura tendance a s'enrouler
 *autour de lui-meme*/
#define COEFF_TARGETSNAKE 1
/* Aggresivite, Plus le coefficient est haut plus le serpent evitera ses congeneres*/
#define COEFF_OTHERSNAKE 3
/* Liberte, plus le coefficient est eleve, plus le serpent voudra eloigner des murs du plateau*/
#define COEFF_PLATEAU 5
/* Prevoyance ,plus le coefficient est eleve plus le serpent se mefira de la tete des autres serpents*/
#define COEFF_HEAD 9



/**
 * @brief init_snake Permet la creation dun serpent dune taille definie
 * @param len taille du serpent
 * @return le serpent cree
 */
snake init_snake(int len,type typesnake){
    snake res;
    res.pos=(coord*)calloc(len,sizeof(coord));
    int i;
    for(i=0;i<len;i++){
        res.pos[i].x=0;
        res.pos[i].y=0;
    }
    res.taille=len;
    res.dir=(direction *) malloc (sizeof(direction));
    res.dir[0]=right;
    res.playType=typesnake;
    res.dead=(bool*) malloc (sizeof(bool));
    res.dead[0]=false;
    return res;
}


void kill_snake(snake s){
    s.dead[0]=true;
}
 
/**
 * @brief delete_snake permet de detruire un snake
 * @param snakeAeffacer serpent a detruire
 */

void delete_snake(snake* snakeAeffacer){

    free(snakeAeffacer->dir);
    free(snakeAeffacer->pos);
    free(snakeAeffacer->dead);
}

/**
 * @brief test si 2 serpents sont égaux
 * @param snake serpent 1
 * @param snake serpent 2
 */
bool egalite_snake(snake s1, snake s2){
    bool res=false;
    if(s1.taille==s2.taille){
        int i=0;
        while(i<s1.taille && s1.pos[i].x==s2.pos[i].x && s1.pos[i].y==s2.pos[i].y){
            i++;
        }
        if(i==s1.taille){
            res=true;
        }
    }
    return res;
}

/**
 * @brief change_IA Permet le changement de l'intelligence artificielle d un serpent
 * @param snake le serpent
 * @param typeAI le nouveau type dAI
 */
void change_IA(snake snake, type typeAI)

{
    snake.playType = typeAI;
}





/**
 * @brief estOccupe Permet de savoir si une case est occupe par un serpent ou un obstacle
 * @param c la coordonnes de la case
 * @param snakes le tableau de serpent
 * @param nombreSerpent le nombre de serpent
 * @param p le plateau
 * @return vrai si occupe
 */
bool estOccupe(coord c ,snake * snakes ,int nombreSerpent, plateau p)

{
    bool res = false;
    int i=0,j=0;

    /*Test du plateau*/
    res = (p.cases[c.x][c.y] == 1);

    /*Test des serpents*/
    for(i= 0 ; i < nombreSerpent && !res ; i++)
    {
        for(j= 0; j < snakes[i].taille && !res ; j++)
        {
            if(!snakes[i].dead[0])
            {
                res  = (snakes[i].pos[j].x==c.x && snakes[i].pos[j].y==c.y);
	    }
        }
    }



    return res;

}
/**
 * @brief estInverse Permet de savoir si deux coordonnees sont inversees utile pour savoir si le
 * serpent ne fais pas marche arriere
 * @param dir1
 * @param dir2
 * @return vrai si lezs cordonnees sont inversees
 */
bool estInverse(direction dir1,direction dir2)
{
    if(dir1 == left )
    {
        return (dir2 == right);
    }
    else if (dir1 == right)
    {
        return (dir2 == left);
    }
    else if (dir1 == up)
    {
        return (dir2 == down);
    }
    else
    {
        return (dir2 == up);
    }
}


/**
 * @brief joueur_strat Fonction de traitement de la strategie du joueur
 *  *Se contente de choisir la direction selectionner par le joueur
 *  *Si la direction est linverse de la direction generale il continu tout droit
 * @param cible le serpent a determiner la direction
 * @param toucheJoueur la direction choisi par le joueur
 * @return la direction apres analyse
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
 * @brief convertDirectionToCoord Permet de convertir une direction en coordonnees
 *Exemple "haut" devient "0,-1"
 * @param dir la direction a convertir
 * @return la coordonnee
 */
coord convertDirectionToCoord(direction dir)
{
    coord res;

    if(dir == left)
    {
        res.x =-1;
        res.y = 0;
    }
    else if(dir == right)
    {
        res.x = 1;
        res.y = 0;
    }
    else if(dir == up)
    {
        res.x = 0;
        res.y = -1;
    }
    else
    {
        res.x = 0;
        res.y = 1;
    }

    return res;

}
/**
 * @brief tournerAntiHoraire permet de selectionner une direction qui se trouve a gauche de la direction en parametre
 *
 * @param dir la direction
 * @return la direction a gauche
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
 * @brief idle_strat Fonction de traitement de la strategie AI IDLE
 * *le serpent se contente daller tout droit sauf sil rencontre un obstacle
 * *si les trois directions possibles sont occupee le serpent se suicide en allant tout droit dans lobstacle
 * @param cible le serpent a determine rla direction
 * @param snakes le tableau des serpents
 * @param nombreSerpent le nombre de serpents
 * @param p le plateau de jeu
 * @return la direction selectionne par la strategie
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
 * @brief calculDistanceTaxicab Permet de calculer la distance entre deux coordonnees selon la methode du TaxiCab
 * ( ou de Manhattan)
 *
 * @param cor1 la coordonnee 1
 * @param cor2 la coordonnee 2
 * @return la distance de Manhattan entre les deux cordonnees
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
 * @brief calculPoidsTableau permet de calculer l influence des murs du plateaux sur une coordonnees donnees
 * Plus la case est eloigné des murs du tableau plus le poids est eleve
 * @note COEFF_PLATEAU est le coefficient de multiplication du poids
 * @param cor la coordonnee
 * @param p le plateau de jeu
 * @return le poids de la case par rapport a l'influence du plateau
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
 * @brief calculPoidsSerpent permet de calculer le poids d'un case par rapport a l'influence des serpent
 * Plus un serpent est eloigne de la case plus le poids qu'il attribut est eleve
 * le serpent cible est egalement pris en compte dans le calcul mais possede un coefficient different des autres serpents
 * le poids est calcule pour tous les serpents et pour tous leurs membres du corps
 *
 * @note COEFF_TARGETSNAKE le coefficient de multiplication du serpent cible
 * @note COEFF_OTHERSNAKE le coefficient de multiplication des autres serpent
 * @note COEFF_HEAD le coefficent de multiplication des tete des serpent (cible exclue)
 * @param pos la coordonnees
 * @param cible le serpent cible
 * @param snakes la liste des serpent
 * @param nombreSerpent le nombre de serpent
 * @param p le plateau de jeu
 * @return le poids calcule
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
            if(!snakes[i].dead[0])
            {
                for(j = 0; j < snakes[i].taille ; j++)
                {
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
 * @brief defensiv_strat Fonction de traitement de la strategie AI DEFENSIVE
 * *Le serpent cherche à etre le plus eloigne possible des autres serpents et notamment du joueur
 * *Le serpent cherche à s'approcher le plus possible du centre
 * *Le serpent cherche a eviter de s'enrouler sur lui-meme
 * *Le serpent calcule les poids des cases adjacents est cherche celle qui a le plus de poids
 * *Si le serpent ne trouve aucune cases adjacentes il se suicide
 * @param cible le serpent cible
 * @param snakes le tableau des snakes
 * @param nombreSerpent le nombre de serpent
 * @param p le plateau de jeu
 * @return la direction choisi par le serpent
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
            poidscurrent += calculPoidsTableau(coor,p);
            poidscurrent += calculPoidsSerpent(coor,cible,snakes,nombreSerpent,p);


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
 * @brief choix_strategie Fonction permettant de choisir la direction du serpent selon sa strategie mise en place
 * @param cible le serpent à derterminer la direction
 * @param snakes lensemble des serpents
 * @param p le plateau de jeu
 * @param toucheJoueur la touche presse par le joueur pendant le debut du tour
 * @return la direction choisi par la strategie
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
        return 0;
        break;
    default :
        return toucheJoueur;
        break;
    }
}
