#ifndef __JEU_H
#define __JEU_H

typedef struct {int x;int y;} Coord;

Coord* init_coord_snake(Coord* l,int longsnake);
void add_coord_snake(Coord* l,int longsnake,Coord direction);

#endif
