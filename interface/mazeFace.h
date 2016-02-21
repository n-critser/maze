#ifndef MAZEFACE_H
#define MAZEFACE_H

void sys_io_restore();
void maze_game_cleanup(int sig);
void set_maze_ioconf();
int maze_play(struct yxGrid * maze);


#endif
