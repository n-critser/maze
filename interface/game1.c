#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

void center(int row, char * title);
void bomb (char *message);
void showmaze(void);

WINDOW *mazewin;

int main(){
        int ch; 
        initscr();
        keypad(mazewin,TRUE);
        //box(stdscr, '*','*');
        center(4, "hello world");
        center(6, "cattle dung smaples from temecula");
        refresh();
        
        
        //getchar();
        if (( mazewin= newwin(10,30,4,26))==NULL){
                center(7, "unable to allocate window memory\n");
                bomb("Dying a quick death");
        }

        mvwaddstr(mazewin,1,7,"maze window");
        mvwaddstr(mazewin,5,3,"Press ~ key to quit");
        mvwaddstr(mazewin,8,4,"Press ENTER to go back");
        box(mazewin,'*','-');
        
        wrefresh(mazewin);
        noecho();
        do {
                ch = wgetch(mazewin);
                switch(ch){
                case KEY_DOWN:
                        mvwaddstr(mazewin,1,7,"Down\n");
                        //showmaze();
                        break;
                case KEY_UP:
                        mvwaddstr(mazewin,8,8,"Up\n");
                        break;
                case KEY_LEFT:
                        mvwaddstr(mazewin,5,4,"Left\n");
                        break;
                case KEY_RIGHT:
                        mvwaddstr(mazewin,5,12,"Right\n");
                        break;
                default:
                        break;
                        
                }
                showmaze();
                
        } while (ch != '~');

        
        endwin();

        return 0;
        
}

void showmaze(void){
        /* get maze window size */
        int mWidth,mHeight;
        getmaxyx(mazewin,mHeight,mWidth);
        //mvwaddstr(mazewin,mHeight-1,mWidth/2,"height= %d , width = %d");
                  //("height= %d , width = %d",mHeight,mWidth)); 
        touchwin(mazewin);
        wrefresh(mazewin);
        getchar();
        touchwin(stdscr);
        refresh();
}

void bomb (char * message){
        addstr(message);
        refresh();
        endwin();
        exit(1);
}

void center(int row, char *title){
        int len, height, indent, y, width;
        getmaxyx(stdscr, y, width);
        height = y;
        height /=2;
        len = strlen(title);
        indent = width - len;
        indent /=2;
        
        mvaddstr(row,indent,title);
        refresh();
}

