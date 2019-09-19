//Karol Pawlak

#include <stdio.h>
#include <stdlib.h>
#include "game_functions.h"

int main(int argc, char *argv[])
{
    //needed for differen random numbers
    srand(time(NULL));

    printf("\nName of my Program %s\n", argv[0]);
    printf("\nGame mode: %s\n", argv[1]);
    printf("\nNumber of bombs: %s\n", argv[2]);

    int _of_bombs = atoi(argv[2]);
    int size = DIM;
    struct locations *   bombs = (struct locations * ) malloc(sizeof(struct locations)  * 2) ;

    //bomb 1
    //bombs[0].x = 1;
    //bombs[0].y  = 1;
    //bombs[0].found = false;

    //bomb 2
    //bombs[1].x = 2;
    //bombs[1].y  = 3;
    //bombs[1].found = false;

    //for loop to populate new bombs with -1 and false
    //this intializes all the bombs
    for (int i = 0; i < _of_bombs; i++)
    {
        bombs[i].x = -1;
        bombs[i].y = -1;
        bombs[i].found = false;
    }

    //generate random coordinates of the bombs
    for (int i = 0; i < _of_bombs; i++)
    {
        //base case, the first bomb is generated
        if (i == 0)
        {
            int x = rand() % 4;
            int y = rand() % 4;
            bombs[i].x = x;
            bombs[i].y = y;
        }

        else
        {
            bool checkDuplicate = true;
            while (checkDuplicate)
            {
                int bombsChecked = 0;
                int x1 = rand() % 4;
                int y1 = rand() % 4;
                //for loop to check all the previous bombs generated and eliminate duplicate
                for (int j = 0; j < (_of_bombs - 1); j++)
                {
                    if (bombs[j].x != x1 && bombs[j].y != y1)
                    {
                        bombsChecked = bombsChecked + 1;
                    }
                }
                //if all the bombs have been checked for dupliactes, exit the loop
                if (bombsChecked == (_of_bombs - 1))
                {
                    bombs[i].x = x1;
                    bombs[i].y = y1;
                    checkDuplicate = false;
                }
            }
        }
    }
    //Printing locations of all the bombs for testing purposes
    printf("Bomb 1 ");
    printf("X :%d ", bombs[0].x);
    printf("Y :%d\n", bombs[0].y);
    printf("Bomb 2 ");
    printf("X :%d ", bombs[1].x);
    printf("Y :%d\n", bombs[1].y);
    printf("Bomb 3 ");
    printf("X :%d ", bombs[2].x);
    printf("Y :%d\n", bombs[2].y);


    int bomb_location_info[4][4] =    { 1, 1, 1, 0,
                                        1, 0, 2, 1,
                                        1, 1, 2, 0,
                                        0, 0, 1, 1};

    int known_location_info[4][4] =   { UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
                                        UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
                                        UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
                                        UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};

    int compareClues = strcmp(argv[1], "clues");
    int compareNoClues = strcmp(argv[1], "noclues");
    if (compareClues == 0)
    {
        bool checkForBombs = true;
        int clue1x;
        int clue1y;
        int clue2x;
        int clue2y;
        while (checkForBombs)
        {
            //create two clues
            int no_of_clues = 2;
            for (int i = 0; i < no_of_clues; i++)
            {
                clue1x = rand() % 4;
                clue1y = rand() % 4;
                bool clueDuplicate = true;
                while (clueDuplicate)
                {
                    clue2x = rand() % 4;
                    clue2y = rand() % 4;
                    if (clue1x != clue2x && clue1y != clue2y)
                    {
                        clueDuplicate = false;
                    }
                }
            }

            //now the two clues have been generated
            //checking if the clues match a position of a bomb
            bool clue1Bomb = false;
            bool clue2Bomb = false;
            for (int i = 0; i < _of_bombs; i++)
            {
                if (clue1x == bombs[i].x && clue1y == bombs[i].y)
                {
                    clue1Bomb = true;
                }

                if (clue2x == bombs[i].x && clue2y == bombs[i].y)
                {
                    clue2Bomb = true;
                }
            }

            if (clue1Bomb == false && clue2Bomb == false)
            {
                checkForBombs = false;
            }

        }
        //printf("Clue 1 x : %d\n", clue1x);
        //printf("Clue 1 y : %d\n", clue1y);
        //printf("Clue 2 x : %d\n", clue2x);
        //printf("Clue 2 y : %d\n", clue2y);
        update_known_info(clue1y, clue1x, bomb_location_info, known_location_info);
        update_known_info(clue2y, clue2x, bomb_location_info, known_location_info);

        start_game(bombs, bomb_location_info, size, known_location_info, _of_bombs);

    }

    else if (compareNoClues == 0)
    {
        start_game(bombs, bomb_location_info, size, known_location_info, _of_bombs);
    }
    else
    {
        printf("ERROR - Wrong command line argument! Please make sure it's either clues or noclues.");
    }
    free(bombs);
}
