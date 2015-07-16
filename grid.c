#include<stdio.h>




void build_grid(int row, int col){
        int grid[col][row];
        int i,j;
        for (i = 0 ; i < col; i++){
                for (j=0; j< row; j++){
                        if (i %3 == 0){
                                grid[i][j]=1;
                        }else {
                                grid[i][j]=0;
                        }
                        printf("grid[%d][%d]=%d",i,j,grid[i][j]);
                }
        }       
        
}

