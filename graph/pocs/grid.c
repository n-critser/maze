#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include "queue.h"
#define log(expr) printf(#expr " %s\n", expr)


/* need a Queue for BFS
   linkedList for adjList
   
 */





/* only need one int ** grid for the maze
 * 
 *
 *
 */
/*
struct yxGrid {
        int rows;
        int cols;
        int **grid;
        int **maze;
        int dist_to_goal;
        char border;
        char wall;
        char pChar;
        char gChar;
        struct pos{
                int y;
                int x;
        }current,goalPos,playerPos;
} ;
*/
int  is_free(struct yxGrid *gridP);
void start_game_message(struct yxGrid *gridP);
void instructions(void);


struct yxGrid * init_grid(int row, int col, int pChar , int gChar,int wall, int border){
        struct yxGrid *gridP;
        gridP=malloc(sizeof(struct yxGrid));
        gridP->rows=row;
        gridP->cols=col;
        assert(row > 0);
        assert(col > 0);
        assert(gridP->rows > 0);
        assert(gridP->cols > 0);

        gridP->grid = (int **)malloc(sizeof(int *) * row);
        gridP->grid[0] = (int *)malloc(sizeof(int) * col * row);
        /* set pChar and gChar positions on the grid */
        int i,j;
        for(i = 0; i < gridP->rows; i++){
                gridP->grid[i] = (*gridP->grid + gridP->cols * i);
        }
        
        for (i = 0 ; i < gridP->rows; i++){
                for (j=0; j< gridP->cols; j++){
                        gridP->grid[i][j] = -1;
                }
        }

        
        srand(time(NULL));
        
        gridP->border=border;
        gridP->wall=wall;
        gridP->pChar=pChar;
        gridP->gChar=gChar;
        
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
        
        gridP->grid[goalY][goalX]=gridP->gChar;
        gridP->grid[playerY][playerX]=gridP->pChar;
        start_game_message(gridP);
        return gridP;

}

int destroy_grid(struct yxGrid *gridP){
        free(gridP->grid[0]);
        free(gridP->grid );
        printf("size of gridP : %ld\n",sizeof(gridP));
        free(gridP);
        printf("size of gridP : %ld\n",sizeof(gridP));
        return 0;
}


int build_grid(struct yxGrid *gridP ){
        //int row, int col, int pChar , int gChar, int wall , int border;
        int i,j;
        double num=-1.0;
        for (i = 0 ; i < gridP->rows; i++){
                for (j=0; j< gridP->cols; j++){

                        if (i == gridP->playerPos.y && j== gridP->playerPos.x)
                                continue;
                        else if (i == gridP->goalPos.y && j== gridP->goalPos.x){
                                continue;
                        }
                        // Removed the border for now till the maze builder works
                        //  else if (i == 0 || j==0 || j== COLS-1 || i== ROWS-1)
                        //        num = -1;

                                
                        else {
                                num = (rand()%2);
                        }
                        gridP->grid[i][j]=num;
                        gridP->current.y=i;
                        gridP->current.x=j;
                }
        }

        return 0;
}

static int print_grid(struct yxGrid * gridP){
        int i,j;
        for (i = 0 ; i < gridP->rows; i++){
                for (j=0; j< gridP->cols; j++){
                        if (gridP->grid[i][j] < 0)
                                printf(" %c ",gridP->border);
                        else if (gridP->grid[i][j] == gridP->pChar)
                                printf(" %c ",gridP->pChar);
                        else if (gridP->grid[i][j] == gridP->gChar)
                                printf(" %c ",gridP->gChar);
                        else
                                printf(" %d ",gridP->grid[i][j]);
                }
                printf("\n");
        }
        return 0;
}

void show_grid(struct yxGrid * gridP){
        print_grid(gridP);
}

int  is_free(struct yxGrid *gridP){
        //printf ("gridP->current.y= %d gridP->current.x=%d ",gridP->current.y,gridP->current.x);
        return 0;//gridP->grid[gridP.current.x][current.y];
}

int play(char * pChar){
        printf("now starting game: PChar = %s" , pChar);
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

void start_game_message(struct yxGrid * gridP){
        printf("Characters for the game\n"
               "pChar = %c\n"
               "gChar   = %c\n"
               "wall   = %c\n"
               "border = %c\n", gridP->pChar,gridP->gChar,gridP->wall,gridP->border);
        printf ("Positions: \n"
                "player y= %d,x= %d\n"
                "goal   y= %d,x= %d\n",
                gridP->playerPos.y,gridP->playerPos.x,
                gridP->goalPos.y,gridP->goalPos.x);
                
        instructions();

}


void instructions(void){
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
