#include "struct.h"
#include "jeu.h"
#include "snake.h"
#include "affiche.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>

float partie(){
/*LE SNAKE*/
    snake snak=init_snake(4,joueur);
    snak.pos[0].x=10;snak.pos[0].y=10;
    snak.pos[1].x=9;snak.pos[1].y=10;
    snak.pos[2].x=8;snak.pos[2].y=10;
    snak.pos[3].x=7;snak.pos[3].y=10;
/*LE SCHLANGA*/
    snake schlanga=init_snake(4,idle);
    schlanga.pos[0].x=15;schlanga.pos[0].y=15;
    schlanga.pos[1].x=16;schlanga.pos[1].y=15;
    schlanga.pos[2].x=17;schlanga.pos[2].y=15;
    schlanga.pos[3].x=18;schlanga.pos[3].y=15;
    schlanga.dir[0]=left;
    snake* s=(snake*) malloc (2*sizeof(snake));
    s[0]=snak;
    s[1]=schlanga;


/*INITILAISATION*/
	/*DEBUT DU JEU*/


	int taille_plateau=0;
	printf("\n****LE JEU VA COMMENCER****\n\n");
	printf("\nSaisissez la taille_plateau du tableau (minimum 20x20) puis ENTER\n");

	scanf("%d",&taille_plateau);
	if( taille_plateau<=19 ){ printf("\n! Erreur de saisie:dimension trop petite ou saisie differente d'un nombre !\nMode par defaut: dim=20\n"); taille_plateau=20 ;}
	

	printf("\nReady!\n");
	printf("Pour se deplacer:\n     ^\n     |\n     z\n<--q    d-->\n     s\n     |\n     v\n");
	system("sleep 1;clear");


	/*time->score*/
    time_t temps1,temps2;
	time(&temps1);
   
	plateau p=init_plateau(taille_plateau);
    affiche(p,s,2);

/*JEU*/
    depart(s,2,p);
    
    while(win(jouer(s,2,p),s,2)){
        affiche(p,s,2);
    }

	time(&temps2);
	float t=difftime(temps2,temps1);
    printf("Bravo !\nTu as tenus %f secondes.\n", t );
	return t;
}

void afficher_score(){
    FILE* fichier = NULL;
    fichier = fopen("score.txt", "r");
	float res;
	float max=0;
    if (fichier != NULL)
    {
		int i=0;
       	fscanf(fichier, "%f ", &res);
        printf("%deme score: %f\n",i, res);
		if( res>max ){ max=res; }
		while( res!=-1 ){
			i=i+1;
        	fscanf(fichier, "%f ", &res);
        	if( res!=-1 ){printf("%deme score: %f\n",i, res);}
			if( res>max ){ max=res; }
		}
		printf("\n **1er**     meilleur score: %f\n", max);
        fclose(fichier);
    }
}

void write_score(float score_de_la_partie){
	FILE *fr=fopen("score.txt","r");
	int i=0;
	float a[100];
	fscanf(fr,"%f ",&a[i]);
	while( a[i]!=-1 ){
		i=i+1;
		fscanf(fr,"%f ",&a[i]);
	}
	fclose(fr);

	FILE *fw=fopen("score.txt","w");
	int j;
	for(j=0;j<i;j=j+1){ fprintf(fw,"%f ",a[j]);}
	fprintf(fw,"%f ",score_de_la_partie);
	fprintf(fw,"-1 ");

	fclose(fw);
}


int main()
{
	/*MENU*/
	printf("Saisissez le numreo puis ENTER pour acceder à votre programme\n");
	printf("\n1) Jouer\n2) Voir les scores\n3) Quitter\n");
	int replay=0;
	scanf("%d",&replay);


	if( replay!=1 &&  replay!=2 &&  replay!=3 ){ printf("\n! Erreur de saisie:hors borne ou saisie differente d'un nombre !\nMode par defaut: jouer\n"); replay=1;}

	if( replay==3 ){ printf("\n**Au revoir**\n"); exit(1); }
	else if( replay==2 ){ 
		/*score();*/
		printf("\nscores (en s):\n");
		afficher_score();
		
	}

	replay=1;

	/*LES PARTIES JOUEES*/
	while( replay==1 ){

		write_score( partie() );

		/*PARTIE POUR RECOMMENCER UNE PARTIE*/

		printf("\nVoulez vous refaire une partie?\nSi oui ecrivez 1 puis ENTER, si non ecrivez 0 puis ENTER\n");

		scanf("%d",&replay);


		if( replay!=0 && replay!=1 ){ printf("\n! Erreur de saisie !\nMode par defaut: Quitter\n"); replay=0 ;}

	}
	printf("\n**Au revoir**\n");

    return 0;
}

