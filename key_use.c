/* gcc -Wall key_use.c -lncurses*/
#include <stdio.h>
#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

#define MAZE_W 60
#define MAZE_H 40

int starty = 0;
int startx = 0;

/* picture menu showing move directions */
char * choices [] = {
        "Up" ,
        "Left",
        "Right",
        "Down ",
        "DEAD",
};

int n_choices = sizeof(choices)/sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);
void show_maze(WINDOW *maze);
void build_maze(WINDOW *maze);

/* main loop */
int main(){
        /* pointers to windows */
        WINDOW *menu_win;
        WINDOW *maze;
        int mainY,mainX, mazeY,mazeX;
        
        
        refresh();
        int highlight = 1;
        int choice =0;
        int c;

        initscr();
        clear();
        noecho();
        cbreak();
        getmaxyx(stdscr,mainY,mainX);
        mvprintw(30, 0, "Main window dimensions\n Rows= %3d , Cols=%3d", mainY, mainX);
        starty = (mainY - HEIGHT)/ 3;
        startx = (mainX - WIDTH)/ 3;
        mazeY = mainY/2;
        mazeX = mainX/2;
        mvprintw(33, 0, "menu window dimensions\n Rows= %3d , Cols=%3d", starty, startx);
        mvprintw(35, 0, "maze window dimensions\n Rows= %3d , Cols=%3d", mazeY, mazeX);
        menu_win = newwin(HEIGHT, WIDTH, starty, startx);
        //maze = newwin(MAZE_H,MAZE_W,mazeY,mazeX);
        maze = newwin(mazeY,mazeX,mazeY,mazeX);
        keypad(menu_win, TRUE);
        
        mvprintw(0,0,"uSE aRROWS to go up and down, and press enter to select");
        refresh();
        print_menu(menu_win, highlight);
        show_maze(maze);
        build_maze(maze);
        int goY,goX;
        goY=goX=1;
        
        while(1){
                c = wgetch(menu_win);
                mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                switch(c){

                case KEY_UP: /*good */
                        if(highlight ==1)
                                highlight = n_choices;
                        else
                                --highlight;
                        if (goY>1 ){
                                mvwprintw(maze,goY,goX,"%c",' ');
                                mvwprintw(maze,--goY,goX,"%c",'X');
                        }
                        else {
                                mvwprintw(maze,goY,goX,"%c",'X');
                        }
                        highlight = 1;
                        wrefresh(maze);
                        break;
                case KEY_DOWN: /* */
                        if(highlight == n_choices)
                                highlight =1 ;
                        else
                                ++highlight;
                        if (goY<mazeY-2 ){
                                mvwprintw(maze,goY,goX,"%c",' ');
                                mvwprintw(maze,++goY,goX,"%c",'X');
                        }
                        else {
                                mvwprintw(maze,goY,goX,"%c",'X');
                        }
                        highlight = 4;
                        wrefresh(maze);
                        break;
                        
                case KEY_LEFT: /*   */
                        if (goX> 1 ){
                                mvwprintw(maze,goY,goX,"%c",' ');
                                mvwprintw(maze,goY,--goX,"%c",'X');
                        }
                        else {
                                mvwprintw(maze,goY,goX,"%c",'X');
                        }
                        highlight = 2;
                        wrefresh(maze);
                        break;
                case KEY_RIGHT:
                        if (goX<mazeX-2  ){
                                mvwprintw(maze,goY,goX,"%c",' ');
                                //waddch(maze,' ');
                                mvwprintw(maze,goY,++goX,"%c",'X');
                        }
                        else {
                                mvwprintw(maze,goY,goX,"%c",'X');
                        }
                        highlight = 3;
                        wrefresh(maze);
                        break;
                case 10:
                        choice = highlight;
                        break;
                default:
                        mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                        refresh();
                        break;
                }
                print_menu(menu_win,highlight);
                if (choice != 0)
                        break;
        }
        mvprintw(23,0,"You chose choice %d with choice string %s\n",choice,choices[choice-1]);
        clrtoeol();
        refresh();
        endwin();
        return 0;
}

/* refresh and show the menu while the updated highlighted choice */
void print_menu(WINDOW * menu_win, int highlight){
        int x,y,i;
        y = 2;
        x = 2;
        box (menu_win, 0,0);
        for (i=0; i< n_choices; i++){
                if (highlight ==i+1){
                        wattron(menu_win,A_REVERSE);
                        mvwprintw(menu_win,y,x,"%s",choices[i]);
                        wattroff(menu_win,A_REVERSE);
                }
                else
                        mvwprintw(menu_win,y,x,"%s",choices[i]);
                ++y;
        }
        wrefresh(menu_win);
}

/* refresh the maze with the correct data  */
void show_maze(WINDOW *maze){
        int y,x,i;
        i=0;
        y = 3;
        x = 3;
        box (maze,0,0);
        mvwprintw(maze,y,x,"I=%d, %s",i,"helloworld");
        wrefresh(maze);
}


void build_maze(WINDOW *maze){
        int row,col;
        getmaxyx(maze,row,col);
        int grid [col][row];
        int i,j;
        for (i = 0 ; i < col; i++){
                for (j=0; j< row; j++){
                        if (i %3 == 0){
                                grid[i][j]=1;
                        }else {
                                grid[i][j]=0;
                        }
                        mvwprintw(maze,j,i,"%d",grid[i][j]);
                        wrefresh(maze);
                        
                }
        }       

}


void build_grid(WINDOW *win, int row, int col){
        int grid[col][row];
        int i,j;
        for (i = 0 ; i < col; i++){
                for (j=0; j< row; j++){
                        if (i %3 == 0){
                                grid[i][j]=1;
                        }else {
                                grid[i][j]=0;
                        }
                        mvwprintw(win,j,i,"%d",grid[i][j]);
                        wrefresh(win);
                        
                }
        }       
        
}

