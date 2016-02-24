#include<stdio.h>
#include<stdlib.h>

typedef struct {int x;int y;} Coord;

void init_tableau(int** tableau,int dim){
	int i,j;
	for(i=0;i<dim;i=i+1){
		for(j=0;j<dim;j=j+1){
			tableau[i][j]=0;
		}
	}	
}


void appplique_partie(int** tableau,Coord* l,int longsnake){
	int i;
	tableau[ l[0].x ][ l[0].y ]=2;

	for(i=1;i<longsnake;i=i+1){
		tableau[ l[i].x ][ l[i].y ]=1;
	}
}

Coord traduction_saisie(int input)
{
		if( (a==8 ) ){ v=-1;h=0; }
		if( (a==4 ) ){ v=0;h=-1; }
		if( (a==6 ) ){ v=0;h=1; }
		if( (a==2 ) ){ v=1;h=0; }

		Coord res;
		res.x=v;
		res.y=h;
		return res;

}

int** jouer_Tour(int input){
		Coord direction = traduction_saisie(input);
		init_tableau(tableau,dim);
		add_coord_snake(l,longsnake,direction);
		appplique_partie(tableau,l,longsnake);
	return t;
}



