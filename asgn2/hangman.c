#include "hangman_strings.h"

/*
* Purpose:          Determine whether a char is lower-case.
*
*                   For this assignment only, YOU MAY NOT USE islower().  I
*                   want you to get experience in comparing character
*                   values.  So you will write code that checks whether c
*                   is between 'a' and 'z'.
*
* Parameter:        c   - A character.  Literally any byte value 0 to 255.
*
* Return value:     1 (true) if c is a lower-case letter (between 'a' and 'z').
*                   0 (false) otherwise.
*/
bool is_lowercase_letter(char c) {
    return (c >= 'a' && c <= 'z'); // returns 1 if the passed char is within 97('a') and 122('z');
				   // else will return 0 if passed char is below or above those values
}


/*
* Purpose:          Determine whether a string contains a character.
*
*                   To determine whether the string contains the given
*                   character, you may use strlen() and a "for" loop, or
*                   you may use strchr().  Use the commands "man 3 strlen"
*                   and "man 3 strchr" to read more about these functions.
*                   Look near the end of the man page for "RETURN VALUE"
*                   for the best summary.
*
* Parameters:       string  - the string to search within
*                   ch      - the character to search for
*
* Return value:     1 if the string contains the character.
*                   0 otherwise
*/
bool string_contains_character(const char *string, char ch) {
	for (int i = 0; i < strlen(string); ++i) { // for loop that will loop through the length of the string 
		if (string[i] == ch) return true; // if string at current index is equal to the passed char we return true and break out of for loop early
	}

	return false; // if we loop through the whole string without finding a match we return false 
}


/*
* Purpose:          Determine whether the length and contents of a secret
*                   are valid.  As described in the assignment PDF, valid
*                   secrets have a length that is no more than MAX_LENGTH
*                   (which already is defined for you in
*                   hangman_strings.h), and they must consist of only
*                   lower-case letters and the three punctuation characters
*                   '-', '\'', and ' '.
*
*                   Use strlen() to confirm that the length of the secret
*                   does not exceed MAX_LENGTH.  If it does, use printf()
*                   and MSG_LONG_SECRET_d to print an error and return
*                   false.  (Look in hangman_strings.h to see what
*                   MSG_LONG_SECRET_d represents.)
*
*                   Using a "for" loop, verify that all of the secret's
*                   characters are valid.  That is, that they are
*                   lower-case letters and the three kinds of punctuation.
*                   If any of the characters is illegal, then use printf()
*                   and MSG_INVALID_CHAR_c to print an error and return
*                   false.  (Look in hangman_strings.h to see what
*                   MSG_LONG_SECRET_d represents.)
*
*                   Hint:  You can test that a character of the string is
*                   punctuation using individual "==" comparisions, or you
*                   can use your function string_contains_character() and
*                   the string "punctuation" (which is defined for you in
*                   hangman_strings.h).
*
* Parameter:        secret  - A string that represents the secret to test.
*
* Return Value:     If the secret is valid, then return true.
*                   Otherwise return false.
*/
bool is_valid_secret(const char *secret) {
	
	char validPunctuation[] = " '-"; // string of valid punctuation

	// base case if statment
	if(strlen(secret) > MAX_LENGTH) { //if the length of secret is larger than MAX_LENGTH(256) 
		printf(MSG_LONG_SECRET_d, MAX_LENGTH); // print the message 
		return false; // and break out of function early by returning false
	}

	// for loop that will go from i = 0 to the length of secret
	for (int i = 0; i < strlen(secret); i++) {
		if (is_lowercase_letter(secret[i])) continue; // checks if the char at secret[i] is lowercase if it is we continue

		if (strchr(punctuation, secret[i]) != NULL) continue;


		if (string_contains_character(validPunctuation, secret[i])) continue; // checks if current char at secret[i] is within the validPuncutation string 
	

		// if one or the other fails we print the message and return false breaking out of function early
		printf(MSG_INVALID_CHAR_c, secret[i]);
	       	return false;
	}

// if we get through the whole for loop with no issues we know the secret string is valid and return true
    return true;
}


/*
* Purpose:          Prompt for and return a character.  If the character is
*                   '\n' (end of line), then get another character.
*
* Parameter:        None.
*
* Return value:     A character.
*/
char prompt_for_and_read_character(void) {
    //               1. Use printf() and MSG_PROMPT to print the prompt.

    //               2. Create a do-while loop.

    //               3. In the body of the loop use getchar() to read an
    //                  int.  (The function is called getchar(), but it
    //                  also might return EOF, and so we need to store
    //                  its return value in an int.)

    //               4. In the condition of the do-while loop check if
    //                  the character is '\n'.  Stay in the loop if it is.

    //               5. If the character is EOF, then call exit(0).

    //               6. Return the character.
    
	int c; // int c decalred to store the value of getchar()
	
	printf(MSG_PROMPT); // print the message to ask for input


	do { // initlaize the do while

		c = getchar(); // call the getchar() function and pass the inputted value into c

		if (c == EOF) { // if c is equal to the End of File we enter body
			exit(0); // return exit code of 0 to terminate
		}

	} while (c  == '\n'); // keep asking while if user is only pressing enter key


// once user enters a character return the char
    return (char)c; // cast it to a char
}

// function used to check if all letters in secret word have been guessed
// we pass in the secret word and an array of bool of size 26 when true means we have gussed that letter
// false means we havnt guessed it
bool all_letters_revealed(const char *secret, const bool guessed[26]) {
    int index = 0; // declare index to move through the secret word array
    while (secret[index] != '\0') { // while secret at current index isnt the null terminator
        if (is_lowercase_letter(secret[index]) && !guessed[secret[index] - 'a']) { // if the letter at i is lowercase
										   // AND if that letter hasnt been guessed
            return false; // return false because at least one letter hasnt been reveled
        }
        index++; // move up to the next index
    }

    // if the above passes we have fully reveled the word return true
    return true;
}

void printSecret(const char *secret, const bool guessed[26]) {
	printf("    Phrase: ");
	// for loop that goes through the through each character until the null terminator
	for (int i = 0; secret[i] != '\0'; i++) {
		char c = secret[i]; // assign the current character to c
		if (is_lowercase_letter(c)) { // checks if c is lowercase
			putchar(guessed[c - 'a'] ? c : '_'); //if guessed bool array at index 'c' - 'a' is true we print the c
			// if its false we print the '_'
		} else {
			// show punctuation/space immediately
			putchar(c);
		}
	}
	printf("\n"); // new line
}

void printEliminated(const bool eliminated[26]) {
	printf("Eliminated: ");
	// for loop to loop through the eleminated characters
	for (int i = 0; i < 26; i++) {
		if (eliminated[i]) putchar('a' + i); // if eleminated at current index is true
		// we print 'a' + current index ex 'a' = 97 index = 6, 97 + 6 = 'g';
	}
	printf("\n\n"); //print new line
}



//print board function used to print the hangman map
// pass in the secret word, bool array og guessed letter, bool array of eleminated letter and number of wrong guesses
void print_board(int wrong) {
    // print the current state of hangman at array wrong, so whatever number out wrong is
    printf("%s", arts[wrong]);
    printf("\n");
}

// actual game function that will take the secret message as the input
void run_hangman(const char *secret) {
    bool guessed[26]    = {0};  // correct letters
    bool eliminated[26] = {0};  // wrong letters
    int  wrong = 0; // counter for how many worng guesses we've done

    // If the phrase has no letters (only punctuation), the player already won.
    if (all_letters_revealed(secret, guessed)) {
        print_board(wrong);
	printSecret(secret, guessed);
	printEliminated(eliminated);
        printf(MSG_WIN_s, secret);
        return;
    }

    // Initial board
    print_board(wrong);
    printSecret(secret, guessed);
    printEliminated(eliminated);

    // for loop being used as a while loo[
    for (;;) {
        char ch = prompt_for_and_read_character();  // call the promt fucntion and pass that value to char ch

        // Only lowercase letters are valid guesses to process
        if (!is_lowercase_letter(ch)) {
            // Ignore invalid input without reprinting board
            continue;
        }

        int idx = ch - 'a'; // index will be used for guessed letter and eleminated letters arrays

        // Repeated guess (either previously correct or previously eliminated) ignore it
        if (guessed[idx] || eliminated[idx]) {
            continue;
        }


	// call the string contains function and pass in the secret word and current ch
        if (string_contains_character(secret, ch)) {
            // if correct guess, guessed at index is set to true
            guessed[idx] = true;

	    // call the all letters revealed function and pass in the word and guessed array
	    // if all letter revealed is true we end the game and print the whole word with win message
            if (all_letters_revealed(secret, guessed)) {
                print_board(wrong); // revealed word
		printSecret(secret, guessed);
		printEliminated(eliminated);
                printf(MSG_WIN_s, secret); // win message
                return;
            }

            // show updated board after a NEW valid guess
            print_board(wrong);
	    printSecret(secret, guessed);
	    printEliminated(eliminated);
        } else {
            // wrong guesses
            eliminated[idx] = true; // eleminated at current index is set to true, we "cant" guess this letter anymore
            wrong++;//add one to the amount of wrong guesses

	    // if statment used to check against the max mistakes 6
            if (wrong >= LOSING_MISTAKE) { // if its greater or equal to losing mistake we enter
                print_board(wrong); // print current board
		printSecret(secret, guessed);
		printEliminated(eliminated);
                printf(MSG_LOSE_s, secret); // print the loosing message
                return; //end early
            }

            // show updated board after a NEW wrong guess
            print_board(wrong);
	    printSecret(secret, guessed);
	    printEliminated(eliminated);
        }
    }
}


/*
* See Section 2 of the assignment PDF.
*
* Write a function-header comment for this function.
* We are going to grade the comments in this function.
*/





/*
* Purpose:          Run the hangman game.
*
*                     1. Check the value of argc to confirm that the user
*                        runs hangman with a "secret" on the command line.
*                        If the user puts the wrong number of arguments on
*                        the command line, then using printf() and
*                        MSG_WRONG_NUM_ARGS to report an error, and then
*                        "return 1".
*                     2. Call is_valid_secret().  If the function
*                        returns false, then "return 1;".
*                     3. Call run_hangman(secret).
*                     4. Return 0.
*
* Parameters:       argc    - The number of command-line arguments from main().
*                   argv    - An array of strings from main().
*
* Return value:     0 if no error.  1 otherwise.
*/
int main(int argc, char **argv) {

	if (argc != 2) {
		printf(MSG_WRONG_NUM_ARGS);
		return 1;
	}

	const char *secret = argv[1];

	if (!is_valid_secret(secret)) {
		return 1;
	}
	run_hangman(secret);


    return 0; // Replace this line with your source code.
}
