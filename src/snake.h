#ifndef __SNAKE_H
#define __SNAKE_H


typedef struct Coord Coord;


struct Coord{int x;int y;} ;


void init_coord_snake(Coord* l,int longsnake);
void add_coord_snake(Coord* l,int longsnake,Coord direction);

#endif
