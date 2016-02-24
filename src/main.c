#include<stdio.h>
#include<stdlib.h>
#include "jeu.h"
#include "snake.h"
#include "affichage.h"



/*---------------LE MAIN--------------------*/

int main() {
/*dimension du tableau*/
	int dim=10;
/*	printf("dimension du terrain:>7\n");
	scanf("%d",&dim);
	while( dim<7 ){	printf("dimension du terrain:>7\n");scanf("%d",&dim);}
*/

/*initialisation*/
	int i;
	int** tableau;
	tableau=malloc(dim*sizeof(int*));
	for(i=0;i<dim;i=i+1){ tableau[i]=malloc(dim*sizeof(int));}
	init_tableau(tableau,dim);

	int longsnake=5;
	Coord* l=(Coord*)malloc(longsnake*sizeof(Coord));
	init_coord_snake(l,longsnake);

	init_tableau(tableau,dim);
	appplique_partie(tableau,l,longsnake);
	system("clear");
	afficher(tableau,dim);


/*mouvement snake*/
	int a;
	for(i=0;i<10;i=i+1){
		afficher_direction();
		scanf("%d",&a);
		while( a!=8 && a!=4 && a!=6 && a!=2 ){printf("resaisissez:");scanf("%d",&a);}

		system("clear");
		afficher(jouer_Tour(a,tableau,dim,l,longsnake),dim);

	}

	free(tableau);
	return 0;
}
