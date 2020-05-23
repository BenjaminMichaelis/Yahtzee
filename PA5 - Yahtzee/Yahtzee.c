#include "Yahtzee.h"

int runmenu(void) //run yahtzee menu and return user selection input
{
    int menu_input = 0;
    printf("\nMAIN MENU\n");
    printf("1. Print game rules\n");
    printf("2. Start a game of Yahtzee\n");
    printf("3. Exit\n");
    scanf_s("%d", &menu_input);
    return menu_input;
}

void print_rules(void) // print game rules for yahtzee
{
    printf("The Rules of Yahtzee:\n\nThe scorecard used for Yahtzee is composed of two sections.A upper sectionand a lower section. \nA total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\nThe upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\nIf a player rolls four 3s, then the score placed in the 3s box is the sum of the dice which is 12. \nOnce a player has chosen to score a box, it may not be changedand the combination is no longer in play for future rounds.\nIf the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the players overall score as a bonus.\nThe lower section contains a number of poker like combinations.\n\n");
}

void yahtzee_controller() //controls the running of a game of yahtzee
{
    int dice_roll[5], roll_times = 0, game_combination_input = 0,
        confirmation = -1, replace_die_YN, save_result = 0,
        bonus_score_result = 0;
    int player1_score[15] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1 }, player2_score[15] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
    int switch_player_times = 0;
    srand((unsigned int)time(NULL)); //prepare for random dice roll

    while (switch_player_times < 13)
    {
        //player 1
        printf("\nPlayer 1s Turn\n");
        confirmation = -1, save_result = 0;

        continue_on(); //have user enter any key to continue to roll dice

        roll_dice(dice_roll, 5, &roll_times); //roll 5 dice randomly and store in array
        display_dice_values(dice_roll, 5);//display each dice value on screen

        while (confirmation != 1 && roll_times < 3)
        {
            //if total number of rolls for round is less than three, asks player is they want to use roll for one of game combos
            confirmation = check_YN_with_player();
            if (confirmation == 1)
            {
                break;
                //game_combination_input = run_game_combinations_menu(); 

            }
            else if (confirmation == 0)
            {
                confirmation = -1;
                replace_die_check(dice_roll, &roll_times); // do you want to replace some of the dice or not
                ++roll_times; // add too roll times if they kept individual die or rerolled all, (dont count each individual roll if keeping some)
            }
        }
        if (roll_times >= 3 || confirmation == 1)
        {
            while (save_result == 0)
            {
                game_combination_input = run_game_combinations_menu() - 1;//combinations 1-13
                save_result = save_score(player1_score, game_combination_input, dice_roll);
                if (save_result == 0)// only prints if it still is invalid, other wise will return 1 for save_result and won't run this
                {
                    printf("You have already selected that previously, you cannot select it again, choose another combination to use");
                }
            }


            roll_times = 0;
        }

        bonus_score_result = bonus_score_check(player1_score, player2_score);
        display_scores(player1_score, player2_score, 1, bonus_score_result);

        //player2 
        printf("\nPlayer 2s Turn\n");
        confirmation = -1, save_result = 0;
        continue_on(); //have user enter any key to continue to roll dice

        roll_dice(dice_roll, 5, &roll_times); //roll 5 dice randomly and store in array
        display_dice_values(dice_roll, 5);//display each dice value on screen


        while (confirmation != 1 && roll_times < 3)
        {
            //if total number of rolls for round is less than three, asks player is they want to use roll for one of game combos
            confirmation = check_YN_with_player();
            if (confirmation == 1)
            {
                break;
                //game_combination_input = run_game_combinations_menu(); 

            }
            else if (confirmation == 0)
            {
                confirmation = -1;
                replace_die_check(dice_roll, &roll_times); // do you want to replace some of the dice or not
                ++roll_times; // add too roll times if they kept individual die or rerolled all, (dont count each individual roll if keeping some)
            }
        }
        if (roll_times >= 3 || confirmation == 1)
        {
            while (save_result == 0)
            {
                game_combination_input = run_game_combinations_menu() - 1;//combinations 1-13
                save_result = save_score(player2_score, game_combination_input, dice_roll);
                if (save_result == 0)// only prints if it still is invalid, other wise will return 1 for save_result and won't run this
                {
                    printf("You have already selected that previously, you cannot select it again, choose another combination to use");
                }
            }


            roll_times = 0;
        }
        bonus_score_result = bonus_score_check(player1_score, player2_score);
        display_scores(player1_score, player2_score, 2, bonus_score_result);

        ++switch_player_times;

    }
    bonus_score_result = bonus_score_check(player1_score, player2_score);
    run_add_total_scores(player1_score, player2_score);
    printf("Final Scores:\n\n");
    display_scores(player1_score, player2_score, 3, bonus_score_result);
}

    


void roll_dice(int dice[], int num_items, int* roll_dice_ptr) // rolls 5 random dice values
{
        int index = 0;
        for (; index < num_items; ++index)
        {
            dice[index] = rand() % 6 + 1;
        }
        ++ *roll_dice_ptr;
}

int roll_die() //rolls one dice value
{
    int die;
    die = rand() % 6 + 1;
    return die;
}

int choose_die_replace() //choose which 1 dice you want to reroll
{
    int die_number = -1;
    do
    {
        printf("Enter the number for the die (1-5) you want to re-roll\n");
        scanf_s("%d", &die_number);
    } while (die_number < 1 && die_number > 5);
    die_number = die_number - 1; //translate: go from die number to index number
    return die_number;
}

int bonus_score_check(int player1_score[], int player2_score[]) //is score for sum >= 63 so add on bonus points or no
{
    int index = 0, index1 = 0, sumplayer1 = 0, sumplayer2 = 0, send_result = 0;

    for (; index < 5; ++index)
    {
        if (player1_score[index] != -1)
        {
            sumplayer1 = player1_score[index] + sumplayer1;
        }
    }
    for (; index1 < 5; ++index1)
    {
        if (player1_score[index1] != -1)
        {
            sumplayer2 = player1_score[index1] + sumplayer2;
        }
    }
    if (sumplayer1 >= 63)
    {
        player1_score[13] = 35;
        send_result = 1;
    }
    if (sumplayer2 >= 63)
    {
        player2_score[13] = 35;
        send_result = 2;
    }
    if (sumplayer1 >= 63 && sumplayer2 >= 63)
    {
        send_result = 3;
    }

    return send_result;
}

void run_add_total_scores(int player1_score[], int player2_score[]) //add up players total scores
{
    int index = 0, index1 = 0, sumplayer1 = 0, sumplayer2 = 0;
    for (; index < 14; ++index)
    {
        if (player1_score[index] != -1)
        {
            sumplayer1 = player1_score[index] + sumplayer1;
        }
    }
    player1_score[14] = sumplayer1;
    for (; index1 < 14; ++index1)
    {
        if (player1_score[index1] != -1)
        {
            sumplayer2 = player2_score[index1] + sumplayer2;
        }
    }
    player2_score[14] = sumplayer2;

}

void display_dice_values(int dice_roll[], int num_items)
{
    int index = 0;
    for (; index < num_items; ++index)
    {
        printf("dice[%d]: %d\n", index + 1, dice_roll[index]);
    }
}

void display_scores(int player1_score[], int player2_score[], int which_to_display, int bonus_score_check)
{
    if (which_to_display == 1)
    {
        printf("\nPlayer 1 Score\n");
        printf("Ones: %d\n", player1_score[0]);
        printf("Twos: %d\n", player1_score[1]);
        printf("Threes: %d\n", player1_score[2]);
        printf("Fours: %d\n", player1_score[3]);
        printf("Fives: %d\n", player1_score[4]);
        printf("Sixes: %d\n", player1_score[5]);
        if (bonus_score_check == 1 || bonus_score_check == 3)
        {
            printf("Bonus: %d\n", player1_score[13]);
        }
        printf("Three of a kind: %d\n", player1_score[6]);
        printf("Four of a kind: %d\n", player1_score[7]);
        printf("Full House: %d\n", player1_score[8]);
        printf("Small Straight: %d\n", player1_score[9]);
        printf("Large Straight: %d\n", player1_score[10]);
        printf("Chance: %d\n", player1_score[11]);
        printf("Yahtzee: %d\n", player1_score[12]);
        

    }
        else if (which_to_display == 2)
        {
            printf("\nPlayer 2 Score\n");
            printf("Ones: %d\n", player2_score[0]);
            printf("Twos: %d\n", player2_score[1]);
            printf("Threes: %d\n", player2_score[2]);
            printf("Fours: %d\n", player2_score[3]);
            printf("Fives: %d\n", player2_score[4]);
            printf("Sixes: %d\n", player2_score[5]);
            if (bonus_score_check == 2 || bonus_score_check == 3)
            {
                printf("Bonus: %d\n", player2_score[13]);
            }
            printf("Three of a kind: %d\n", player2_score[6]);
            printf("Four of a kind: %d\n", player2_score[7]);
            printf("Full House: %d\n", player2_score[8]);
            printf("Small Straight: %d\n", player2_score[9]);
            printf("Large Straight: %d\n", player2_score[10]);
            printf("Chance: %d\n", player2_score[11]);
            printf("Yahtzee: %d\n", player2_score[12]);
        }
        else if (which_to_display == 3)
        {
            printf("\nPlayer 1 Score\n");
            printf("Ones: %d\n", player1_score[0]);
            printf("Twos: %d\n", player1_score[1]);
            printf("Threes: %d\n", player1_score[2]);
            printf("Fours: %d\n", player1_score[3]);
            printf("Fives: %d\n", player1_score[4]);
            printf("Sixes: %d\n", player1_score[5]);
            if (bonus_score_check == 1 || bonus_score_check == 3)
            {
                printf("Bonus: %d\n", player1_score[13]);
            }
            printf("Three of a kind: %d\n", player1_score[6]);
            printf("Four of a kind: %d\n", player1_score[7]);
            printf("Full House: %d\n", player1_score[8]);
            printf("Small Straight: %d\n", player1_score[9]);
            printf("Large Straight: %d\n", player1_score[10]);
            printf("Chance: %d\n", player1_score[11]);
            printf("Yahtzee: %d\n", player1_score[12]);
            printf("Total Score: %d\n", player1_score[14]);

            printf("\nPlayer 2 Score\n");
            printf("Ones: %d\n", player2_score[0]);
            printf("Twos: %d\n", player2_score[1]);
            printf("Threes: %d\n", player2_score[2]);
            printf("Fours: %d\n", player2_score[3]);
            printf("Fives: %d\n", player2_score[4]);
            printf("Sixes: %d\n", player2_score[5]);
            if (bonus_score_check == 2 || bonus_score_check == 3)
            {
                printf("Bonus: %d\n", player2_score[13]);
            }
            printf("Three of a kind: %d\n", player2_score[6]);
            printf("Four of a kind: %d\n", player2_score[7]);
            printf("Full House: %d\n", player2_score[8]);
            printf("Small Straight: %d\n", player2_score[9]);
            printf("Large Straight: %d\n", player2_score[10]);
            printf("Chance: %d\n", player2_score[11]);
            printf("Yahtzee: %d\n", player2_score[12]);
            printf("Total Score: %d\n", player2_score[14]);
        }
    if (player1_score[14] > player2_score[14])
    {
        printf("\nPlayer 1 Wins!!\n");
    }
    if (player2_score[14] > player1_score[14])
    {
        printf("\nPlayer 2 Wins!!\n");
    }
}


void continue_on()
{
    char character;
    printf("Press any key to continue on to the roll dice\n");
    //while (character == NULL)
    
    scanf(" %c", &character);
    
    //if (character != NULL)

}

int run_game_combinations_menu()
{
    int response = -1;
    do
    {
        printf("What combination would you like to use?\n");
        printf("(Press the number of the combination you would like to use.)\n");
        printf("%d. Sum of 1's.\n", 1);
        printf("%d. Sum of 2's.\n", 2);
        printf("%d. Sum of 3's.\n", 3);
        printf("%d. Sum of 4's.\n", 4);
        printf("%d. Sum of 5's.\n", 5);
        printf("%d. Sum of 6's.\n", 6);
        printf("%d. Three of a Kind.\n", 7);
        printf("%d. Four of a Kind.\n", 8);
        printf("%d. Full House.\n", 9);
        printf("%d. Small Straight.\n", 10);
        printf("%d. Large Straight.\n", 11);
        printf("%d. Yahtzee.\n", 12);
        printf("%d. Chance\n", 13);
        scanf_s("%d", &response);
    } while (response < 1 || response > 13);
    return response;
}

int check_YN_with_player()
{
    int response = -1, check = -1;
    char charresponse;
    do
    {
        printf("Would you like to use this role for a game combination?(press Y for yes or N for no)\n");
        scanf(" %c", &charresponse);
        if (charresponse == 'Y' || charresponse == 'N' || charresponse == 'y' || charresponse == 'n') // check they entered a Y or N
        {
            check = 1;
        }
    } while (check != 1); // loop until they enter a Y or N
    response = transfer_char_to_int(charresponse);
    return response; //return response in integer form
}

int replace_die_check(int dice_roll[], int *roll_times)
{
    int replace_die, input = 1, check, reuse = -1, reroll_inputs[5] = { -5,-5,-5,-5,-5 };
    char charresponse;
    do //reroll all die or just some of the die
    {
        printf("Would you like to keep any of the dice you just rolled? (press Y for yes and N for no)\n");
        scanf(" %c", &charresponse);
        check = transfer_char_to_int(charresponse);
    } while (check != 0 && check != 1); //keep looping until they enter a Y or n
    if (check == 0)//reroll all of the dice
    {//reroll all die
        roll_dice(dice_roll, 5, &roll_times); //roll 5 dice randomly and store in array
        display_dice_values(dice_roll, 5);//display each dice value on screen
    }
    else if (check == 1) //if they want to just replace certain die, keep looping until they have replaced the die they want to or all 5 die once each
    {
        while (input == 1)//that they have more dice to replace
        {

            replace_die = choose_die_replace();
            
                int index = 0, found = 0, num_items = 5; //sequential search for dice to see if they have entered to reroll it already

                for (; index <= num_items && !found; ++index)
                {
                    if (reroll_inputs[index] == replace_die)
                    {
                        found = 1;
                        reuse = index;
                    }
                }
                found = 0;

            if (reuse == -1) // check that they can't reroll the same dice multiple times
            {
                dice_roll[replace_die] = roll_die();
                printf("Your new dice values are now\n");
                display_dice_values(dice_roll, 5);//display each dice value on screen
                reroll_inputs[replace_die] = replace_die;
            }
            else if (reuse != -1)
            {
                printf("You have already re-rolled that dice, you cannot reroll again\n");
            }
            printf("Do you want to re-roll another die? Y or N (you may only reroll each individual die once)\n");
            scanf(" %c", &charresponse);
            input = transfer_char_to_int(charresponse);

        }
        ++roll_times; // add too roll times if they kept individual die or rerolled all, (dont count each individual roll if keeping some)
    }
}

int transfer_char_to_int(char charresponse)
{
    int check = -1;
if (charresponse == 'Y' || charresponse == 'y') // check that they entered in a Y or N
{
    check = 1;
}
if (charresponse == 'N' || charresponse == 'n')
{
    check = 0;
}
return check;
}

int save_score(int player_score[], int game_combination_input, int dice_roll[])
{
    int check_combination_result, check_exits_result;
    int sum = 0;
    int game_combination_input1 = game_combination_input + 1;
    check_combination_result = check_combination_input(game_combination_input, player_score); // make sure it hasn't been used already
    if (check_combination_result == 0)
    {
        return 0;
    }
    check_exits_result = check_combination_exists(game_combination_input, dice_roll); //if returns 0, then save score of 0 because doesn't exist in dice, if returns 1, add up dice if need be and then save to score
    if (check_exits_result == 0)
    {
        player_score[game_combination_input] = 0;
    }
    else if (game_combination_input1 <= 8)
    {
        
            if (check_combination_result == 1)
            {
                
                if (check_exits_result == 1)
                {
                    player_score[game_combination_input] = run_add_scores_of_dice(game_combination_input, dice_roll);
                }
            }
    }
    else if (game_combination_input1 == 13)//chance = sum of all face values on the dice
    {

        int pos = 1, index = 0;
        for (; index < 5; ++index) //check each dice for the number that were checking (1-6)
            {
            sum = dice_roll[index] + sum;
            }
        player_score[game_combination_input] = sum;
    }
    else if (game_combination_input1 > 8)
    {
        if (game_combination_input1 == 9)//full house = 25
        {
            player_score[game_combination_input] = 25;
        }
        else if (game_combination_input1 == 10)//small straight  = 30
        {
            player_score[game_combination_input] = 30;
        }
        else if (game_combination_input1 == 11)//large straight = 40
        {
            player_score[game_combination_input] = 40;
        }
        else if (game_combination_input1 == 12)//yahtzee = 50
        {
            player_score[game_combination_input] = 50;
        }
    }
    return 1;
}
int check_combination_input(int game_combination_input, int player_score[])// make sure it hasn't been used already
{
    int valid = 0;
    
    int index = 0, found = 0, num_items = 5; 
        if (player_score[game_combination_input] == -1) //if it equals -1 aka it has not been saved too yes, return a 1 to allow to save score to that spot, if not return 0 and loop to rerun combination choosing
        {
            found = 1;
        }
        return found; 
}

int check_combination_exists(int game_combination_input, int dice_roll[]) //if returns 0, then save score of 0 because doesn't exist in dice, if returns 1, add up dice if need be and then save to score
{
    //sort dice
    int passes = 0, temp = 0, index = 0;
    int game_combination_input1 = game_combination_input + 1;

        for (passes = 1; passes < 5; ++passes)
        {
            for (index = 0; index < 5 - passes; ++index)
            {
                if (dice_roll[index] > dice_roll[index + 1])
                {
                    //swap
                    temp = dice_roll[index];
                    dice_roll[index] = dice_roll[index + 1];
                    dice_roll[index + 1] = temp;
                }
            }
        }
    //search for combo existing
    int foundresult = 0;
    if (game_combination_input1 <= 6)
    {
        int index = 0, found = 0;

        for (; index < 5 && !found; ++index)
        {
            if (dice_roll[index] == game_combination_input1) // if found = 1 return found because then it will add score, if return 0 then it will eventually save score as 0 there
            {
                foundresult = 1;
                found = 1;
            }
        }
    }
    else if (game_combination_input1 == 7) // 3 of a kind
    {
        int index = 0, pos = 1, found = 0, found1 = 0, how_many_in_a_row = 0;

        for (; pos <= 6 && !found; ++pos) //check numbers 1-6
        {
            for (; index < 5 && !found1; ++index) //check each dice for the number that were checking (1-6)
            {
                if (dice_roll[index] == pos) // if found = 1 return found because then it will add score, if return 0 then it will eventually save score as 0 there
                {
                    ++how_many_in_a_row;
                    if (how_many_in_a_row >= 3) //check if theres 3 or more of a kind
                    {
                        found1 = 1;
                        found = 1;
                    }
                }
            }
            if (how_many_in_a_row < 3)
            {
                how_many_in_a_row = 0;
            }
            index = 0;
        }
        if (how_many_in_a_row >= 3)
            foundresult = 1;
    }
    else if (game_combination_input1 == 8) // 4 of a kind
    {
        int index = 0, pos = 1, found = 0, found1 = 0, how_many_in_a_row = 0;

        for (; pos <= 6 && !found; ++pos) //check numbers 1-6
        {
            for (; index < 5 && !found1; ++index) //check each dice for the number that were checking (1-6)
            {
                if (dice_roll[index] == pos) // if found = 1 return found because then it will add score, if return 0 then it will eventually save score as 0 there
                {
                    ++how_many_in_a_row;
                    if (how_many_in_a_row >= 4) //check if theres 4 or more of a kind
                    {
                        found1 = 1;
                        found = 1;
                    }
                }
            }
            if (how_many_in_a_row < 4)
            {
                how_many_in_a_row = 0;
            }
            index = 0;
        }
        if (how_many_in_a_row >= 4)
            foundresult = 1;
    }
    else if (game_combination_input1 == 9) // full house
    {
        int index = 0, pos = 1, found = 0, found1 = 0, how_many_in_a_row = 0, temp = 0, how_many_in_a_row2 = 0;

        for (; pos <= 6 && !found; ++pos) //check numbers 1-6
        {
            for (; index < 5 && !found1; ++index) //check each dice for the number that were checking (1-6)
            {
                if (dice_roll[index] == pos) // if found = 1 return found because then it will add score, if return 0 then it will eventually save score as 0 there
                {
                    ++how_many_in_a_row;
                    if (how_many_in_a_row >= 3) //check if theres 3 or more of a kind
                    {
                        found1 = 1;
                        found = 1;
                        temp = pos; // dont check again for that number that has 3 or more
                    }
                }
            }
            if (how_many_in_a_row < 3)
            {
                how_many_in_a_row = 0;
            }
            index = 0;
        }
        found = 0;
        found1 = 0;//reset to search again for 2 in a row
        for (; pos <= 6 && !found; ++pos) //check numbers 1-6
        {
            for (; index <= 5 && !found1; ++index) //check each dice for the number that were checking (1-6)
            {
                if (dice_roll[index] == pos && pos != temp) // if found = 1 return found because then it will add score, if return 0 then it will eventually save score as 0 there
                {
                    ++how_many_in_a_row2;
                    if (how_many_in_a_row2 >= 2) //check if theres 2 or more of a kind
                    {
                        found1 = 1;
                        found = 1;

                    }
                }
            }
            if (how_many_in_a_row < 2)
            {
                how_many_in_a_row = 0;
            }
        }
        if (how_many_in_a_row == 3 && how_many_in_a_row2  == 2)
            foundresult = 1;
    }
    else if (game_combination_input1 == 10)// small straight (4 increasing)
    {
    int index = 0, pos = 1, found = 0, found1 = 0, how_many_in_a_row = 0, temp = 0, how_many_in_a_row2 = 0;

    for (; pos <= 3 && !found; ++pos) //check numbers 1-6
    {
        for (; index < 5 && !found1; ++index) //check each dice for the number that were checking (1-6)
        {
            if (dice_roll[index] == pos) // if found = 1 return found because then it will add score, if return 0 then it will eventually save score as 0 there
            {
                ++how_many_in_a_row;
                if (how_many_in_a_row >= 4) //check if theres 4 or more sequentially
                {
                    found1 = 1;
                    found = 1;
                }
                ++pos;
            }
            else if (dice_roll[index] != pos)
            {
                how_many_in_a_row = 0;
            }

        }
        if (how_many_in_a_row < 4)
        {
            how_many_in_a_row = 0;
        }
        index = 0;
    }
    if (how_many_in_a_row >= 4)
        foundresult = 1;
    }
    else if (game_combination_input1 == 11) //large straight (5 increasing)
    {
    int index = 0, pos = 1, found = 0, found1 = 0, how_many_in_a_row = 0, temp = 0, how_many_in_a_row2 = 0;

    for (; pos <= 2 && !found; ++pos) //check numbers 1-6
    {
        for (; index < 5 && !found1; ++index) //check each dice for the number that were checking (1-6)
        {
            if (dice_roll[index] == pos) // if found = 1 return found because then it will add score, if return 0 then it will eventually save score as 0 there
            {
                ++how_many_in_a_row;
                if (how_many_in_a_row >= 5) //check if theres 5 or more sequentially
                {
                    found1 = 1;
                    found = 1;
                }
                ++pos;
            }
            else if (dice_roll[index] != pos)
            {
                how_many_in_a_row = 0;
            }

        }
        if (how_many_in_a_row < 5)
        {
            how_many_in_a_row = 0;
        }
        index = 0;
    }
    if (how_many_in_a_row >= 5)
        foundresult = 1;
    }
    else if (game_combination_input1 == 12) //yahtzee (5 of a kind)
    {
    int index = 0, pos = 1, found = 0, found1 = 0, how_many_in_a_row = 0, temp = 0, how_many_in_a_row2 = 0;

    for (; pos <= 6 && !found; ++pos) //check numbers 1-6
    {
        for (; index <= 5 && !found1; ++index) //check each dice for the number that were checking (1-6)
        {
            if (dice_roll[index] == pos) // if found = 1 return found because then it will add score, if return 0 then it will eventually save score as 0 there
            {
                ++how_many_in_a_row;
                if (how_many_in_a_row >= 5)//check if theres 5 or more of a kind
                {
                    found1 = 1;
                    found = 1;
                }
            }
        }
        if (how_many_in_a_row < 5)
        {
            how_many_in_a_row = 0;
        }
    }
    if (how_many_in_a_row >= 5)
        foundresult = 1;
    }
    else if (game_combination_input1 == 13) //chance (sum of die)
    {
    foundresult = 1;
    }
    return foundresult;
}
int run_add_scores_of_dice(int game_combination_input, int dice_roll[])
{
    int sum = 0;
    int index = 0;
    int game_combination_input1 = game_combination_input + 1;
    for (; index < 5; ++index) //check each dice for the number that were checking (1-6)
    {
        if (dice_roll[index] == game_combination_input1)
            sum = dice_roll[index] + sum;
    }
    return sum;
}
