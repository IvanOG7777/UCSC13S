#include "game.h"
#include "randi.h"
#include "strings.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/*
* Here is an array of player names.  Given a player number i, use the
* player names like this:
*
*   player_name[i]
*
* Following this array declaration is the definition of MAX_PLAYERS.  The
* player number i can be anything from 0 to MAX_PLAYERS - 1.
*/
const char *player_name[] = {

    "Ada Lovelace",
    /*
    * 1815-1852.  Wrote the first algorithm for a computer.
    */

    "Margaret Hamilton",
    /*
    * 1936-.  While in her 20s, lead the team that wrote and tested the
    * Apollo moon program's on-board flight software. Invented the term
    * "software engineering".
    */

    "Katherine Johnson",
    /*
    * 1918-2020.  Mathematician who hand-calculated trajectories for crewed
    * spaceflights.
    */

    "Joy Buolamwini",
    /*
    * ~1989-.  MIT computer scientist who works to challenge racial and
    * gender bias in AI-based decision software.
    */

    "Grace Hopper",
    /*
    * 1906-1992.  Mathematician and computer scientist who made the first
    * machine-independent computer language.
    */

    "Adele Goldberg",
    /*
    * 1945-.  Managed the team at Xerox that developed object-oriented
    * programming and graphical user interfaces.
    */

    "Annie Easley",
    /*
    * 1933-2011.  NASA computer scientist and mathematician who developed
    * algorithms that analyze various power technologies.
    */

    "Jeannette Wing",
    /*
    * 1956-.  Led many research projects as a university professor and as a
    * vice president at Microsoft Research.
    */

    "Mary Kenneth Keller",
    /*
    * 1913-1985.  First person to earn a Ph.D. in computer science in the
    * United States.
    */

    "Megan Smith",
    /*
    * 1964-.  Vice president at Google and 3rd Chief Technology Officer of
    * the United States.
    */

    "Radia Perlman",
    /*
    * 1958-.  Computer programmer and network engineer who invented many
    * network protocols include the Spanning Tree Protocol used by network
    * bridges.
    */
};

/*
* Faces of the die are numbered 0 through 5, and each face has a symbol.
* Create an array of six Symbols that is indexed by the face number.  Then
* you can convert the roll of a die (0-5) into a Symbol by accessing the
* array like this:
*
*    Symbol sym = symbol_of_roll[roll];
*/
const Symbol symbol_of_roll[6] = {
    DOT, // index 0
    DOT, // index 1
    DOT, // index 2
    LEFT, // index 3
    CENTER, // index 4
    RIGHT, // index 5
};

int score[MAX_PLAYERS];

/*
* Purpose:      Return the letter of the Symbol according to this table:
*
*                    sym    return
*                   ------  ------
*                   DOT      '.'
*                   LEFT     'L'
*                   CENTER   'C'
*                   RIGHT    'R'
*
* Parameter:    sym - the Symbol DOT, LEFT, CENTER, or RIGHT.
*
* Returns:      a char that represents the letter of the Symbol.
*/
char letter_of_symbol(Symbol sym) {
	//switch case that passes in sym of type Symbol enum
	switch(sym) {
		// cases will check the passed the sym and return  corresponding charater
		case DOT: return '.'; // case DOT return '.'
		case LEFT: return 'L'; // case LEFT returns 'L'
		case RIGHT: return 'R'; // case RIGHT returns 'R'
		case CENTER: return 'C'; // case CENTER returns 'C'
		default:
			     assert(0);
	}
}

/*
* Purpose:      Compute the minimum of two ints.
*
* Parameters:   ints a and b
*
* Returns:      a or b, whichever is smallest.
*/
int min(int a, int b) {
    // if statment will check if a is less than b
    if (a < b) return a; // if true were return a
    return b; // else were return b
}

/*
* Purpose:      Return the next roll of a CSE 13S die.  That is, call randi(),
*               and then convert the result into a number between 0 and 5.
*
* Parameter:    none
*
* Returns:      An int from 0 to 5 representing a die roll
*/
int rand_roll(void) {
	// call and return the randi function from randi.c
	// we modulo it by 6 to return numbers 0-5
	return randi() % 6;
}

/*
* Purpose:      Compute the number of the player that is to the LEFT of the
*               player with the number given in parameter "player".
*               (See Section 2 of the assignment PDF.)
*
* Parameters:   player      - player number from 0 to num_players - 1
*               num_players - the number of players in this game
*
* Returns:      int from 0 to num_players - 1
*/
int left_of(int player, int num_players) {
	// we return the current playerers index + 1
	// then modulo it but however many players are in the game
	
	// EX: player = 1, num_players = 3;
	//
	// player = 2
	//
	// 2 % 3 = 2
	//
	// return 2
	return (player + 1) % num_players;
}

/*
* Purpose:      Compute the number of the player that is to the RIGHT of the
*               player with the number given in parameter "player".
*               (See Section 2 of the assignment PDF.)
*
* Parameters:   player      - player number from 0 to num_players - 1
*               num_players - the number of players in this game
*
* Returns:      int from 0 to num_players - 1
*/
int right_of(int player, int num_players) {

    // we return the current player index - 1, plus the num_players passed
    // then modulo  it by however many players are in the game
    //
    // EX: player = 1, num_players = 3
    //
    // player = 3
    //
    // 3 % 3 = 0
    //
    // returns 0
    return (player - 1 + num_players) % num_players;
}

/*
* Purpose:      Print all of the players' scores followed by the number of
*               chips in the pot.  The scores are in the array score[],
*               which is delcared near the top of this file.  You can
*               compute the number of chips in the pot (the game has a
*               total of 3 * num_players chips), or you can maintain the
*               pot's score in a new variable that you declare up where the
*               score[] array is.
*
*               Here is an example of the output:

Current scores:
    3 -- Ada Lovelace
    3 -- Margaret Hamilton
    3 -- Katherine Johnson
    0 -- pot

*               If you want, you can use two format strings in the file
*               string.h:  CURRENT_SCORES and SCORE_ds.  Look in strings.h
*               to see what they represent.
*
* Parameter:    num_players - an int which is the number of players.
*
* Returns:      nothing
*/
void print_scores(int num_players) {
	// base casses
	// if the num of players is less than 3 or greater than the allowed max players we return
	if (num_players < 3 || num_players > MAX_PLAYERS){
		return;
	}

	printf(CURRENT_SCORES); // print the current score from STRINGS.h

	int pot = 3 * num_players; // declare pot and fill with 3 *  num_player (3 chips per each player)

	// for loop to print the current players score and name
	for (int i = 0; i < num_players; i++){ // loops from 0 to num_players
		printf(SCORE_ds, score[i], player_name[i]); // prints the format from STRINGS.h
							    // followed by the score and name at current index
		pot -= score[i]; // subtract the current indexes score at i from pot
	}

	printf(SCORE_ds, pot, "pot"); // prits the format from STRINGS.h followed by pot and "pot"
}

/*
* Play the game.  See Section 2 of the assignment PDF for details.
*
* Write a function-header comment for this function.
* We are going to grade the comments in this function.
*/

/*
* Purpose: Runs the LCR game similation 
* Seeds the player RNG with  seed will give each of the num_players player 3 chips then goes in order from 0 -> num_players - 1
* On each players turn they will 'roll' up to min(3, score[i]) dice and for each die move a chip according to LEFT/RIGHT/CENTER/DOT
* After each turn we print the scores
* The game ends when only only player holds 1 - 3 * num_players amount of chips.
*
* Parameters: Seed - unsigned int that will be used on randi().
*			  num_players - number of players min 3 - MAX_PLAYERS(11)
*
*Return: return nothing void
* 
*/
void play_game(unsigned seed, int num_players) { // pass in the unsigned in seed value and the amount of players for the game

	randi_seed(seed); // call the randi_seed() from above and pass in the seed that was passed into the function]
	int pot = 0; // declare pot and set it to 0

	// for loop that will go through each player from 0 - num_players
	for (int i = 0; i < num_players; i++) {
		score[i] = 3; // give the player[i] (score[i]) 3 chips
	}

	print_scores(num_players); // call the print function pass in number of players and print their scores

	// for loop treated as a while loop
	for (;;) {
		// for loop that will go from 0 - num_players
		for (int i = 0; i < num_players; i++) {
			if (score[i] == 0) { // if the player or score in this case at i has 0 chips
				printf(HAS_NO_CHIPS_s, player_name[i]); // print the prompt from STRINGS.h and pass in players name at i
				continue; // continue to next player since current player cant do anything
			}

			printf(TURN_s, player_name[i]); // print the turn prompt from STRINGS.h and the players name
			
			// declare variable named dice
			int dice = min(3, score[i]); // set dice equal to the min between the current players score and 3
						     // if player has more than 3 chips defaults to 3 dice (in game rumes)
						     // if player has between 1-2 chips it will use either 1-2 dice

			// for loop to loop through the amount of dice player has
			// each loop is a different role
			for (int die = 0; die < dice; die++) {
				int roll = rand_roll(); //decalre roll and call the rand_roll function to give us a number
				Symbol symbol = symbol_of_roll[roll]; // decalre symbol of type Symbol
								      // call the symbol_of_roll function and pass in the roll
								      // depeing on number role give use we will get
								      // DOT = 0 - 2
								      // LEFT = 3
								      // CENTER = 4
								      // RIGHT = 5

				printf(ROLLS_c, letter_of_symbol(symbol)); // print the rolls prompt from STRINGS.h
									   // call the letter_ofsymbol function and pass in our symbol
									   // if DOT we get '.'
									   // if LEFT we get 'L'
									   // if CENTER we get 'C'
									   // if RIGHT we get 'R'

				switch (symbol) { // use a switch and pass in the symbol we get from roll
					case RIGHT: { // case for right
							    score[i]--; // subract one chip from the current players score
							    score[right_of(i, num_players)]++; // add that chip to the player to the right of current player
											       // call in the righ_of function and pass in the current players index i and the num of players to calculate
							    printf(GIVES_A_CHIP_TO_s, player_name[right_of(i, num_players)]); // print the give chips promt from STRING.h and get the name of the player to the right of current player
															      // here i just call the function within the player_name array becasue it return the right player anyways
							    break; // break out of switch
						    }
					case LEFT: { // case for left
							   score[i]--; // subtract one chip from current player
							   score[left_of(i, num_players)]++; // add chip to the left of current player
							   printf(GIVES_A_CHIP_TO_s, player_name[left_of(i, num_players)]); // print the give chips prompt from STRINGS.h and get the name of the player to the left of current player
							   break; // break out of switch
						   }
					case CENTER: { // case for center
							     score[i]--; // subtract a chip from current player
							     pot++; // add chip to the pot
							     printf(PUTS_A_CHIP); // call the puts chip in center from STRINGS.h
							     break; // break out of switch
						     }
					case DOT: // case dot do nothing
					default: break; // default swicth case
				}
			}

			print_scores(num_players); // print the current scores of num_players

			// below will check if only one player has any chips in the game
			int playerWithChips = 0; // playerWithChips will count how many players currently have chips
			int lastPlayer = -1; // initlaize to -1 to indicate we havent found any players yet. Helps use prevent using an old or invalid index 

			// for loop that will loop through num_players
			for (int j = 0; j  < num_players; j++) {
				if (score[j] > 0) { // if the players score at i is greater than 0
					playerWithChips++;// weincrement the playerWithChips counter
					lastPlayer = j; // lastPlayer is set to current index of player with chips
				}
			}

			if (playerWithChips == 1) { // if playerWithChips is equal to 1, meaning only one player has chips 
				printf(ONE_PLAYER_HAS_CHIPS); // print the one player has chips promt from STRINGS.h
				printf(WON_s, player_name[lastPlayer]); // print the wont prompt from STRING.h and pass in player at the current index
				return; // return out of the loop end of game
			}
		}
	}
}
