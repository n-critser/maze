#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include "../graph/grid.h"

/*
  struct termios {
  tcflag_t c_iflag;   input specific flags (bitmask)
  tcflag_t c_oflag;     output specific flags (bitmask) 
  tcflag_t c_cflag;     control flags (bitmask)
  tcflag_t c_lflag;     local flags (bitmask) 
  cc_t     c_cc[NCCS];  special characters 
};
 */

enum DIRECTION {north,east,south,west};



struct maze_face{
        char **board;
        int width;
        int height;
        int maze_num;
        int score;
        int x,y;
        int win;
        enum DIRECTION moveDir;
        struct vertex *goal;
        struct vertex *player;
        char pChar,gChar;
        
};

/*original tty setup should be restored on game end */
struct termios restore;

void sys_io_restore(){
        tcsetattr(fileno(stdin),TCSANOW,&restore);
}

void maze_game_clean(int sig){
        sys_io_restore();
}

int set_maze_ioconf(){
        struct termios game_term;
        int fd=fileno(stdin);
        if(fd == -1) {
                printf( "failed to open terminal device\n" );
                return fd;
        }
        tcgetattr(fd,&restore);
        game_term=restore;
        game_term.c_lflag &=~(ICANON|ECHO);
        tcsetattr(fd,TCSANOW,&game_term);
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0)|O_NONBLOCK);
        return 0;
}

int maze_game_init(struct maze_face *face, int width,int height){
        int x,y;
        face->win=0;
        face->pChar='@';
        face->gChar='#';
        face->player=malloc(sizeof(struct vertex));
        face->goal=malloc(sizeof(struct vertex));
        face->width=width;
        face->height=height;
        face->player->x=0;
        face->player->y=0;
        face->goal->x=width-1;
        face->goal->y=height-1;
        face->maze_num=0;
        face->score=0;
        face->board=malloc(sizeof(char *)*width);
        for (x=0; x<width; x++){
                face->board[x] = malloc(sizeof(char)*height);
                for (y=0;y<height;y++)
                        face->board[x][y]='^';
        }
        return 0;
}

int maze_hit_test(struct maze_face *face){

        //int x,y;
        
        if ((face->player-> y == face->goal-> y) && (face->player->x == face->goal->x)){
                face->win=1;
        } else if  ((face->player->y > face->height ) ||
                    (face->player->y < 0)             ||
                    (face->player->x < 0)             ||
                    (face->player->x > face->width)){
                face->win=-1;
        } else
                face->win=0;
        return face->win;
}


int maze_move(struct maze_face *face, enum DIRECTION move){
        printf ("move : %d \n",move);
        switch(move){
        case north:  
                face->player->y--;
                break;

        case east:
                face->player->x++;
                break;
        case south:
                face->player->y++;
                break;
        case west:
                face->player->x--;
                break;
        }
        // test for hit after move
        // could stop move pre-emptively using hit test
        maze_hit_test(face);
        return move;
}

int maze_face_clean(struct maze_face *face) {
	int x;
	for (x=0; x<face->width; x++) {
		free(face->board[x]);
	}
	free(face->board);
        return 0;
}


void maze_show_face(struct maze_face * face){
        int x,y;
        int space=20;
        for(x=0; x<space;x++)
                printf("\n");
        printf ("moveDir = %d\n",face->moveDir);
        printf ("face->win = %d\n",face->win);
        printf("[MAZE#: %d | SCORE: %d]\n", face->maze_num, face->score);
        printf("player(x,y):(%d,%d) ",face->player->x,face->player->y);
        printf("goal(x,y):(%d,%d) ",face->goal->x,face->goal->y);
        printf("\n");
        for (x=0;x<2*face->width;x++)
                printf("-");
        printf("\n");
        /*Height built first then width */
        for (y=0; y<face->height;y++){
                printf("|");
                for (x=0; x<face->width;x++){
                        if ( (y == face->player->y) && (x == face->player-> x)){
                                printf("%c ",face->pChar);
                               
                        } else if ((y == face->goal->y) && (x == face->goal-> x)){
                                printf("%c ",face->gChar);
                        } else {
                                printf("%c ",face->board[x][y]);
                        }
                }
                printf("|\n");
        }
        for (x=0;x<2*face->width;x++)
                printf("-");
        printf("\n");
        
        
}

int maze_test_win(struct maze_face * face){
        if ( face->player == face->goal)
                return 1;
        else
                return 0;
}

int maze_quit(struct maze_face * face){
        
        /* signal will be -1 or some char*/
        maze_face_clean(face);
        int signal='q';
        maze_game_clean(signal);
        return 0;
}

int maze_play(int width, int height){
        struct maze_face face;
        char cmd;
        enum DIRECTION move;
        set_maze_ioconf();
        maze_game_init(&face,width,height);
        maze_show_face(&face);
        while( face.win >= 0){
                while((cmd=getchar())>0){
                        switch(cmd){
                        case 'e':
                                move=north;
                                maze_move(&face,move);
                                break;
                        case 'f':
                                move=east;
                                maze_move(&face,move);
                                break;
                        case 'd':
                                move=west;
                                maze_move(&face,move);
                                break;
                        case 'v':
                                move=south;
                                maze_move(&face,move);
                                break;
                        default:
                                face.x=10;
                                face.y=10;
                                break;
                        }
                        maze_test_win(&face);
                        maze_show_face(&face);
                        
                }
                
        }
        maze_quit(&face);

        
        return -99;        
}




