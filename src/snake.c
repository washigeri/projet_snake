#include<stdio.h>
#include<stdlib.h>
#include "snake.h"


void init_coord_snake(Coord* l,int longsnake){
	int i;
	Coord coord;
	coord.x=2;coord.y=2;
	for(i=0;i<longsnake;i=i+1){
		l[i]=coord;
		coord.x=coord.x+1;
	}

	//return l;
}


void add_coord_snake(Coord* l,int longsnake,Coord direction){
	int i;
	Coord c=l[0];

	for(i=longsnake;i>0;i--){ l[i]=l[i-1];}

	c.x=c.x+direction.x;
	c.y=c.y+direction.y;
	l[0]=c;

}


