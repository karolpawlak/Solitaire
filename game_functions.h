//Karol Pawlak R0010390
//Project 2

#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED

#endif // GAME_FUNCTIONS_H_INCLUDED

#include <stdbool.h>

#define DIM 4
#define UNKNOWN -1
#define BOMB -2

struct locations {
    int x;
    int y;
    bool found;
};

void display(int grid[][DIM], int size);
void update_known_info(int row, int col, int bomb_info[][DIM], int known[][DIM]);
void check_found(int row, int col, struct locations bombs[], int size, bool* found);
char get_userChar();
void start_game(struct locations* bombs, int bomb_location_info[][DIM], int size_of_grid, int players_info[][DIM], int no_of_bombs);

//not used
void update_status(int row, int col, int scores[][DIM], int known[][DIM]);
