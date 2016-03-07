#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef enum {left='q',right='d',up='z',down='s'} direction;

typedef enum {joueur,idle,defensif,offensive} type ;

typedef struct {int x;int y;} coord;

typedef struct {coord* pos;
                int taille;
                direction* dir;
                type playType;
                direction* dir;
                } snake;

typedef struct {int** cases;
                int taille;} plateau;


#endif // STRUCT_H_INCLUDED
