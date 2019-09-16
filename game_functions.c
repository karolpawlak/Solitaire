//Karol Pawlak R0010390
//Project 2

#include <stdio.h>
#include <stdbool.h>
#include "game_functions.h"

void display(int grid[][DIM], int size)
{
    printf("    A B C D \n");
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            printf("A : ");
        }
        else if ( i == 1)
        {
            printf("B : ");
        }
        else if ( i == 2)
        {
            printf("C : ");
        }
        else if ( i == 3)
        {
            printf("D : ");
        }
        for (int j = 0; j < size; j++)
        {
            if (grid[i][j] == -1)
            {
                printf("* ");
            }
            else if (grid[i][j] == -2)
            {
                printf("B ");
            }
            else
            {
                printf("%d ", grid[i][j]);
            }
        }
        printf("\n");
    }

}

void update_known_info(int row, int col, int bomb_info[][DIM], int known[][DIM])
{
    known[row][col] = bomb_info[row][col];
}

char get_userChar()
{
    bool inputCheck = true;

    while (inputCheck)
    {
        char userInput;
        scanf("%c", &userInput);
        getchar(); //collects enter
        if (userInput == 'A' || userInput == 'B' || userInput == 'C' || userInput == 'D')
        {
            return userInput;
            inputCheck = false;
        }
        else
        {
            printf("Please ensure you input A, B, C or D : ");
        }
    }
}

//why is there int size parameter? what for?
void check_found(int row, int col, struct locations bombs[], int size, bool* found)
{
    //bomb 1
    int* bomb1_x = &bombs[0].x;
    int* bomb1_y = &bombs[0].y;
    bool* bomb1_found = &bombs[0].found;

    if (*bomb1_x == col && *bomb1_y == row && *bomb1_found == false)
    {
        bombs[0].found = true;
        *found = true;
    }

    //bomb 2
    int* bomb2_x = &bombs[1].x;
    int* bomb2_y = &bombs[1].y;
    bool* bomb2_found = &bombs[1].found;

    if (*bomb2_x == col && *bomb2_y == row && *bomb2_found == false)
    {
        bombs[1].found = true;
        *found = true;
    }

        //bomb 3
    int* bomb3_x = &bombs[2].x;
    int* bomb3_y = &bombs[2].y;
    bool* bomb3_found = &bombs[2].found;

    if (*bomb3_x == col && *bomb3_y == row && *bomb3_found == false)
    {
        bombs[2].found = true;
        *found = true;
    }

        //bomb 4
    int* bomb4_x = &bombs[3].x;
    int* bomb4_y = &bombs[3].y;
    bool* bomb4_found = &bombs[3].found;

    if (*bomb4_x == col && *bomb4_y == row && *bomb4_found == false)
    {
        bombs[3].found = true;
        *found = true;
    }
}

void start_game(struct locations* bombs, int bomb_location_info[][DIM], int size_of_grid, int players_info[][DIM], int no_of_bombs)
{
    enum game_status {STILL_ALIVE, GAME_OVER};
    enum game_status status = STILL_ALIVE;

    int number_found = 0; //phase 2
    bool bombFound = false;
    int cellCounter = 1;
    /*
    int compareClues = strcmp(argv[1], "clues");
    if (compareClues == 0)
    {
        cellCounter = 3;
        printf("CC3");
    }
    else
    {
        cellCounter = 1;
        printf("CC1");
    }
    */


    //PHASE 1
    while (status == STILL_ALIVE)
    {
        display(players_info, size_of_grid);

        printf("Moves : %d\n", cellCounter);

        //column
        printf("Please enter the column: ");
        char colInput = get_userChar();
        int col = colInput - 'A';

        //row
        printf("Please enter the row: ");
        char rowInput = get_userChar();
        int row = rowInput - 'A';

        cellCounter = cellCounter + 1;

        check_found(row, col, bombs, size_of_grid, &bombFound);

        //if bomb found - game is finished
        if (bombFound)
        {
            players_info[row][col] = BOMB;
            display(players_info, size_of_grid);
            status = GAME_OVER;
            printf("----------------------------------------------\n");
            printf("---------- BOOOOOOOOOOOOOMM ! ----------------\n");
            printf("----------------------------------------------\nGAME OVER");

        }

        //otherwise update
        update_known_info(row, col, bomb_location_info, players_info);
        if (cellCounter == 5)
        {
            display(players_info, size_of_grid);
            printf("----------------------------------------------\n");
            printf("WELL DONE!! INITIATING PHASE 2\n");
            break;
        }

    }

    //PHASE 2
    while (status == STILL_ALIVE)
    {
        bool bombFoundPhase2 = false; //reset if one bomb was already found

        display(players_info, size_of_grid);
        printf("There are %d bombs, enter their positions now.\n", no_of_bombs);

        //column
        printf("Please enter the column: ");
        char colInput = get_userChar();
        int col = colInput - 'A';

        //row
        printf("Please enter the row: ");
        char rowInput = get_userChar();
        int row = rowInput - 'A';

        check_found(row, col, bombs, size_of_grid, &bombFoundPhase2);

        if (bombFoundPhase2)
        {
            printf("Well done! You found a bomb!\n");
            printf("Bombs found : %d", number_found);
            printf("You found a bomb at %c, %c\n", colInput, rowInput);
            players_info[row][col] = BOMB;
            number_found = number_found + 1;

            if (number_found == no_of_bombs)
            {
                printf("----------------------------------------------\n");
                display(players_info, size_of_grid);
                printf("Congratulations! You found all bombs!\nYOU WON!!");
                status = GAME_OVER;
            }
        }
        else
        {
            printf("----------------------------------------------\n");
            printf("No bomb here! GAME OVER");
            status = GAME_OVER;
        }

    }

}
