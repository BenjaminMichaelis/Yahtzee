#pragma warning (disable: 6031)
#ifndef LOOPS_H // guard code
#define LOOPS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>


#endif

#define print_rules_selected 1
#define play_game_selected 2
#define exit_selected 3

int runmenu(void);
void print_rules(void);
void yahtzee_controller(void);
void roll_dice(int dice[], int num_items, int* roll_times_ptr);
void continue_on(void);
int roll_die();
int choose_die_replace(void);
int check_combination_input(int game_combination_input, int player_score[]);
int run_game_combinations_menu(void);
int check_YN_with_player();
void display_dice_values(int dice_roll[], int num_items);
int replace_die_check(int dice_roll[], int *roll_times_ptr);
int transfer_char_to_int(char charresponse);
int save_score(int player1_score[], int game_combination_input, int dice_roll[]);
int check_combination_exists(int game_combination_input, int dice_roll[]);
int run_add_scores_of_dice(int game_combination_input, int dice_roll[]);
void display_scores(int player1_score[], int player2_score[], int which_one_display, int bonus_score_check);
int bonus_score_check(int player1_score[],int player2_score[]); 
void run_add_total_scores(int player1_score[],int player2_score[]);