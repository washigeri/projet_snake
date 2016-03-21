#include "struct.h"
#include "jeu.h"
#include "snake.h"
#include "affiche.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
	
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
    
    while(win(jouer(s,2,p),s,2))

	time(&temps2);
	float t=difftime(temps2,temps1);
    printf("Tu as tenus %f secondes.\n", t );
	return t;
}

void partie_test_collisions(int n){
	plateau p=init_plateau(30);
	snake snak=init_snake(4,joueur);
	snak.pos[0].x=10;snak.pos[0].y=10;
        snak.pos[1].x=9;snak.pos[1].y=10;
        snak.pos[2].x=8;snak.pos[2].y=10;
        snak.pos[3].x=7;snak.pos[3].y=10;
	snake schlanga=init_snake(4,idle);
	schlanga.pos[0].x=15;
        schlanga.pos[1].x=16;
        schlanga.pos[2].x=17;
        schlanga.pos[3].x=18;
        schlanga.dir[0]=left; 
        snake* s=(snake*) malloc (2*sizeof(snake));
        s[0]=snak;
        s[1]=schlanga;
	if(n==1){
		s[1].pos[0].y=15;
		s[1].pos[1].y=15;
		s[1].pos[2].y=15;
		s[1].pos[3].y=15;
	}
	if(n==2){
		s[1].pos[0].y=10;
		s[1].pos[1].y=10;
		s[1].pos[2].y=10;
		s[1].pos[3].y=10;
	}
	while(win(jouer_test_collisions(s,2,p),s,2));
}

void afficher_score(){
    FILE* fichier =NULL; 
    FILE* temp;
    temp=fopen("others/temp.txt","w+");    
    fichier=fopen("others/score.txt", "r");
	float res;
	float max=0;
	int i, len;
	system("cat others/score.txt | wc -l > others/temp.txt");
	fscanf(temp,"%d",&len);
	fclose(temp);
	for(i=0;i<len && i<20;i++){
       	fscanf(fichier, "%f", &res);
       	if( res!=EOF ){printf("[%d]: %f\n",i+1, res);}
		if( res>max ){ max=res; }
	}
	printf("\nMeilleur score: %f\n", max);
    fclose(fichier);
    system("rm -f others/temp.txt");
    
}

void write_score(float score_de_la_partie){
	FILE* fichier=NULL;
	fichier=fopen("others/score.txt","a+");
	fprintf(fichier,"%f\n",score_de_la_partie);
	fclose(fichier);
}


int main()
{
	/*MENU*/
	printf("Saisissez le numreo puis ENTER pour acceder à votre programme\n");
	printf("\n1) Jouer\n2) Voir les scores\n3) Tests collisions\n4) Quitter\n");
	int replay=0;
	scanf("%d",&replay);


	if( replay!=1 &&  replay!=2 &&  replay!=3 ){ printf("\n! Erreur de saisie:hors borne ou saisie differente d'un nombre !\nMode par defaut: jouer\n"); replay=1;}

	if(replay==3){
		system("clear");
		printf("\n1) Collisions mur\n2) Collisions serpent/serpent\n");
		int direction;
		scanf("%d",&direction);
		partie_test_collisions(direction);
	}
			

	if( replay==4 ){ printf("\n**Au revoir**\n"); exit(1); }
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


		if( replay!=0 && replay!=1 ){
		    printf("\n! Erreur de saisie !\nMode par defaut: Quitter\n");
		    replay=0 ;
		}

	}
	printf("\n**Au revoir**\n");

    return 0;
}

