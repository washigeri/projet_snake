#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

snake init_snake(int len){
    snake res;
    res.pos=(coord*)malloc(len*sizeof(coord));
    int i;
    for(i=0;i<len;i++){
            res.pos[i].x=0;
            res.pos[i].y=0;
    }
    res.taille=len;
    res.dir=right;
    return res;
}

