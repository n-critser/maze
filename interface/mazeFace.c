#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

/*
  struct termios {
  tcflag_t c_iflag;   input specific flags (bitmask)
  tcflag_t c_oflag;     output specific flags (bitmask) 
  tcflag_t c_cflag;     control flags (bitmask)
  tcflag_t c_lflag;     local flags (bitmask) 
  cc_t     c_cc[NCCS];  special characters 
};
 */

struct maze_face{
        char **board;
        int width;
        int height;
        int maze_num;
        int score;
        int x,y;
        
};

/*original tty setup should be restored on game end */
struct termios restore;

void sys_io_restore(){
        tcsetattr(fileno(stdin),TCSANOW,&restore);
}

void maze_game_cleanup(int sig){
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
        face->width=width;
        face->height=height;
        face->board=malloc(sizeof(char *)*width);
        for (x=0; x<width; x++){
                face->board[x] = malloc(sizeof(char)*height);
                for (y=0;y<height;y++)
                        face->board[x][y]='^';
        }
        return 0;
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
        printf("[MAZE#: %d | SCORE: %d]\n", face->maze_num, face->score);
        for (x=0;x<2*face->width;x++)
                printf("-");
        printf("\n");
        /*Height built first then width */
        for (y=0; y<face->height;y++){
                printf("|");
                for (x=0; x<face->width;x++){
                        printf("%c ",face->board[x][y]);
                }
                printf("|\n");
        }
        for (x=0;x<2*face->width;x++)
                printf("-");
        printf("\n");
        
        
}

int maze_play(int width, int height){
        struct maze_face face;
        char cmd;
        
        set_maze_ioconf();
        maze_game_init(&face,width,height);
        maze_show_face(&face);
        while((cmd=getchar())>0){
                switch(cmd){
                case 't':
                        face.y--;
                        break;
                default:
                        face.x=10;
                        face.y=10;
                        break;
                }
        }
        maze_face_clean(&face);
        sys_io_restore();
        
        return -99;        
}




