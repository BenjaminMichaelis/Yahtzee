/*
Programmer: Benjamin Michaelis
Program: Yahtzee
Date: 3/2/2020
Description: This program will allow a user to play a game of Yahtzee
*/

#include "Yahtzee.h"
int main(void)
{
    int option = 0, continue_controller = 12;
    while (continue_controller == 12)
    {
        do
        {
            //TODO: Implement do while inside switch with default statements
            option = runmenu();//get user input from menu
        } while (option < 1 || option > 3);
        switch (option)
        {
        case print_rules_selected:
            print_rules();
            break;
        case play_game_selected:
            yahtzee_controller();
            break;
        case exit_selected:
            continue_controller = 0;
            break;
        }
    }

    printf("\n\nThank you for playing this game of yahtzee\n\n");

    return 1;
}