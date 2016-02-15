#ifndef GRID_H_
#define GRID_H_

int build_grid(int,int,int,int,int,int);
void show_grid();
int destroy_grid();

struct vertex{
        int y;
        int x;
};

struct yxGrid * gridP;

#endif
