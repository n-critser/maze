#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "maze.h"
#include "queue.h"
#define log(expr) printf(#expr " %s\n", expr)


/* need a Queue for BFS
   linkedList for adjList
   
 */

int  is_free(int y,int x);
static void start_game_message(void);
static void instructions(void);




/* only need one int ** grid for the maze
 * 
 *
 *
 */
struct yxGrid {
        int rows;
        int cols;
        int **grid;
        int **maze;
        int dist_to_goal;
        char border;
        char wall;
        char player;
        char goal;
        struct pos{
                int y;
                int x;
        }current,goalPos,playerPos;
} *gridP;



static int init_grid(int row, int col, int player , int goal,int wall, int border){
        //arr  = (int **)malloc(sizeof(int *) * r);
        //arr[0] = (int *)malloc(sizeof(int) * c * r);
        srand(time(NULL));
        gridP=malloc(sizeof(struct yxGrid));
        gridP->grid = (int **)malloc(sizeof(int *) * row);
        gridP->grid[0] = (int *)malloc(sizeof(int) * col * row);
        gridP->rows=row;
        gridP->cols=col;
        gridP->border=border;
        gridP->wall=wall;
        gridP->player=player;
        gridP->goal=goal;
        
        int goalY,goalX;
        int playerY,playerX;
        goalY=(rand()%7)+2;
        goalX=(rand()%7)+2;
        gridP->goalPos.y=goalY;
        gridP->goalPos.x=goalX;
        playerY=(rand()%7)+2;
        playerX=(rand()%7)+2;
        gridP->playerPos.y=playerY;
        gridP->playerPos.x=playerX;
        /* set player and goal positions on the grid */
        gridP->grid[goalY][goalX]=gridP->goal;
        gridP->grid[playerY][playerX]=gridP->player;
        start_game_message();
        return sizeof(gridP);
}

int destroy_grid(){
        free(gridP->grid[0]);
        free(gridP->grid );
        printf("size of gridP : %ld\n",sizeof(gridP));
        free(gridP);
        printf("size of gridP : %ld\n",sizeof(gridP));
        return 0;
}


int build_grid(int row, int col, int player , int goal, int wall , int border){
        int i,j;
        init_grid(row,col,player,goal,wall,border);
        double num=-1.0;

        
        //gridP->grid = malloc(row*sizeof(int*));
        //for(i=0;i<row;i++) gridP->grid[i] = malloc(col*sizeof(int));
        for (i = 0 ; i < row; i++){
                //gridP->grid[i][0]=1;
                for (j=0; j< col; j++){

                        if (i == gridP->playerPos.y && j== gridP->playerPos.x)
                                continue;
                        else if (i == gridP->goalPos.y && j== gridP->goalPos.x){
                                continue;
                        }
                        /* Removed the border for now till the maze builder works
                          else if (i == 0 || j==0 || j== COLS-1 || i== ROWS-1)
                                num = -1;
                        */
                                
                        else {
                                /* num = (rand()%9);  */
                                num = (rand()%2);
                        }
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

static int print_grid(struct yxGrid * grid){
        int i,j;
        for (i = 0 ; i < grid->rows; i++){
                for (j=0; j< grid->cols; j++){
                        if (gridP->grid[i][j] < 0)
                                printf(" %c ",gridP->border);
                        else if (gridP->grid[i][j] == gridP->player)
                                printf(" %c ",gridP->player);
                        else if (gridP->grid[i][j] == gridP->goal)
                                printf(" %c ",gridP->goal);
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

int play(char * player){
        printf("now starting game: Player = %s" , player);
        int choice;

        instructions();
        scanf("%d", &choice);
        while (choice != 0){
                switch( choice ){
                case 8:
                        /*move up */
                        break;
                case 2:
                        /*move down */
                        break;
                case 4:
                        /*move left */
                        break;
                case 6:
                        /*move right */
                        break;

                default:
                        /*show command list w-invalid command error */
                        break;

                }
        }       
        return 0;
}

static void start_game_message(void){
        printf("Characters for the game\n"
               "player = %c\n"
               "goal   = %c\n"
               "wall   = %c\n"
               "border = %c\n", gridP->player,gridP->goal,gridP->wall,gridP->border);
        printf ("Positions: \n"
                "player y= %d,x= %d\n"
                "goal   y= %d,x= %d\n",
                gridP->playerPos.y,gridP->playerPos.x,
                gridP->goalPos.y,gridP->goalPos.x);
                
        instructions();

}


static void instructions(void){
        printf("Enter integers for player movement\n"
               " 8 = up\n"
               " 2 = down\n"
               " 4 = left\n"
               " 6 = right\n"
               " 0 to end the game\n");
}


/*Prims algorithm section */
/*
  1 2 3 4 5
  6 7 8 9 a
  b c d e f
  
  Graph = grid[y][x] position is connected to some adjacent position grid[y][x]
  Then we have V = y * x vertices if each position is used (not required)
  how many edges? 

  MST- minimum spanning tree : created an array of  vertices with a pointer to its parent  representing the edges as they were added to tree 
  
  Queue and heap  */



//int move(int direction , struct *yxGrid){
//}
