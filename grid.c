#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "maze.h"
#define log(expr) printf(#expr " %s\n", expr)

#define ROWS 10
#define COLS 10

int  is_free(int y,int x);

struct yxGrid {
        int rows;
        int cols;
        int grid[ROWS][COLS];
        char border;
        char wall;
        struct pos{
                int y;
                int x;
        }current;
} *gridP;



int init_grid(){
        srand(time(NULL));
        gridP=malloc(sizeof(struct yxGrid));
        gridP->rows=ROWS;
        gridP->cols=COLS;
        gridP->border='!';
        gridP->wall='*';
        return sizeof(gridP);
}

int destroy_grid(){
        printf("size of gridP : %ld\n",sizeof(gridP));
        free(gridP);
        printf("size of gridP : %ld\n",sizeof(gridP));
        return 0;
}

int build_grid(int row, int col){
        int i,j;
        init_grid();
        double num=-1.0;
        //gridP->grid = malloc(row*sizeof(int*));
        //for(i=0;i<row;i++) gridP->grid[i] = malloc(col*sizeof(int));
        for (i = 0 ; i < ROWS; i++){
                //gridP->grid[i][0]=1;
                for (j=1; j< COLS; j++){
                        if (i == 0 || j==0 || j== COLS-1 || i== ROWS-1)
                                num = 0;
                        else
                                num = (random()%9)+1;
                        gridP->grid[i][j]=num;
                        gridP->current.y=i;
                        gridP->current.x=j;
                        //printf(" %d ",gridP->grid[i][j]);
                        //is_free(i,j);
                }
                //printf("\n");
        }
        return 0;
}

int print_grid(struct yxGrid * grid){
        int i,j;
        for (i = 0 ; i < ROWS; i++){
                for (j=0; j< COLS; j++){
                        if (gridP->grid[i][j] < 1)
                                printf(" %c ",gridP->border);
                        else
                                printf(" %d ",gridP->grid[i][j]);
                }
                printf("\n");
        }
        return 0;
}

void show_grid(){
        print_grid(gridP);
}

int  is_free(int y,int x){
        printf ("gridP->current.y= %d gridP->current.x=%d ",gridP->current.y,gridP->current.x);
        return gridP->grid[x][y];
}

//int move(int direction , struct *yxGrid){
//}
