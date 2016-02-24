#include<stdio.h>
#include<stdlib.h>
/*les fonctions presentes ici correspondent à l'affichage des infos à l'écran*/

/*affiche le plateau
converti un tableau d'entier en char*/

void afficher(int** t,int dim){
	int i,j;
	for(i=0;i<dim;i=i+1){ printf("---");}
	printf("--\n");
	for(i=0;i<dim;i=i+1){
		printf("|");
		for(j=0;j<dim;j=j+1){
			if( t[i][j]==0 ){ printf("   ");}
			if( t[i][j]==1 ){ printf(" 1 ");}
			if( t[i][j]==2 ){ printf(" 8 ");}
			if( t[i][j]==-1 ){ printf(" X ");}
			if( t[i][j]==-2 ){ printf("XXX");}
		}
		printf("|");
		printf("\n");
	}
	for(i=0;i<dim;i=i+1){ printf("---");}
	printf("--\n");
}

/*affiche les commandes manettes*/

void afficher_direction(){
		printf("\n    ^    \n");
		printf("    8    \n");
		printf(" <4   6> ");
		printf("\n    2    \n");
		printf("    V    \n");
}



/*---------------LE MAIN--------------------*/

int main(){
/*dimension du tableau*/
	int dim;
	printf("dimension du terrain:>7\n");
	scanf("%d",&dim);
	while( dim<7 ){	printf("dimension du terrain:>7\n");scanf("%d",&dim);}


/*initialisation*/
	int i;
	int** tableau;
	tableau=malloc(dim*sizeof(int*));
	for(i=0;i<dim;i=i+1){ tableau[i]=malloc(dim*sizeof(int));}
	init_tableau(tableau,dim);

	int longsnake=5;
	Coord* l=malloc(longsnake*sizeof(Coord));
	l=init_coord_snake(l,longsnake);

	init_tableau(tableau,dim);
	appplique_partie(tableau,l,longsnake);
	system("clear"); 
	afficher(tableau,dim);	


/*mouvement snake*/
	int v,h,a;
	for(i=0;i<10;i=i+1){
		afficher_direction();
		scanf("%d",&a);
		while( a!=8 && a!=4 && a!=6 && a!=2 ){printf("resaisissez:");scanf("%d",&a);}

		
		system("clear"); 
		afficher(tableau,dim);	

	}

	free(tableau);
	return 0;
}	
