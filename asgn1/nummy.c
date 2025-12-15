#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define EPSILON 1e-14

void usage(void) {
    printf("Usage:  ./nummy -e N\n");
    printf("        ./nummy -l N\n");
    printf("        ./nummy -p N\n");
    printf("        ./nummy -s N\n");
    printf("        for positive integer N\n");
    exit(1);
}

// function that calculates the ABS of a double number
// pass in the x value to the function
double absolute_value(double x) {
    return fabs(x); // pass in x value into fabs function and return that value;
}

// function used to calculate the sqrt of a double value x
// using the newton-raphson sqqrt method (nextGuess = 1/2 (current guess + (target / currentGuess));
double my_sqrt(double x) { //pass in the double valued number into the function

    double nextY = 1.0; // declare our next guesss to 1.0;
    double y = 0.0; //declare our storage for out current guess call it y and initalize it to 0

  // while the abs value of our nextGuess and current guess are
  // greater than EPSILON continue with code within
    while (absolute_value(nextY - y) > EPSILON) {
	y = nextY; // set out current guess to out next guess before changing the nextGuess

	nextY = .5 * (y + (x / y)); // calculate the nextGuess using newton-raphson sqrt method
    }

  // once nextY - y is greater than EPSILON we break out and return out nextY
    return nextY;
}

// function used to calculate the e of a given integer number
double my_e(int n) { // pass in our int number to the function to calculate its factorial
	double sum = 1.0; // initalize sum to 1.0
	double  factorial = 1.0; // initlaize our factorial to 1.0

	// base case
	if (n == 0) { // if n is equal to 0 
		return 1; // break out of function early and just return 1
	}

	// for loop that goes from i = 1 to n
	for (int i = 1; i < n; i++) {
		factorial *= i; // calculate our factorial by using previous fact and multiply and sum with current i
		sum += 1.0 / factorial; // calcualte sum using current i and update out previous sum by +=
	}

	return sum; // return the sum once we break out of the for loop
}

//fucntion used to calcualte ln2 by passing in an int n
double my_ln2(int n) { // pass in our n
	double sum = 0.0; // initalize sum to 0. Will be updated within four loop
	double power = 1.0; // initialize 2^i term; starts at 2^0 = 1 and doubles each loop iteration

	// for loop that goes from k = 1 to n
	for (int i = 1; i <= n; i++) {
		power *= 2; // update our power
		sum += 1 / (power * i); // calculate using the ln2 formula and update our sum
	}
	return sum; // return the sum after we break out of the for loop
}

// function used to calculate pi by passing in a integner n
double my_pi(int n) { // pass in n
	double sum = 0.0; // initlaize our sum to 0, will be used to store out sum before multiplying by sqrt(12)
	double power = 1.0; // initialize (-3)^k term; starts at (-3)^0 = 1 and multiplies by -3 each loop

	// For loop that goes from k = 0 to n
	for (int i = 0; i < n; i++) {
		sum += 1.0 / (power * (2 * i + 1)); // update sum by using pi approx formula
		power *= -3.0; // update our power for next itteration
	}

	return my_sqrt(12) * sum; // call out sqrt function pass in 12 and return the sqrt of 12 times our new sum
}

/*
* Example usage:  nummy -p 10
*                 ^     ^  ^---argv[2]
*   argc == 3     ^     ^----argv[1]
*                 ^--------argv[0]
*/
int main(int argc, char **argv) {
    if (argc != 3) {
        usage();
    }
   
    int n = atoi(argv[2]);
   
    if (n <= 0) {
	 usage();
    }

    if (strcmp(argv[1], "-e") == 0) {
	 printf("e is %.13f\n", my_e(n));
    } else if (strcmp(argv[1], "-l") == 0) {
        printf("ln 2 is %.13f\n", my_ln2(n));
    } else if (strcmp(argv[1], "-p") == 0) {
	printf("pi is %.13f\n", my_pi(n));
    } else if (strcmp(argv[1], "-s") == 0) {
	printf("sqrt(%d) is %.13f\n", n, my_sqrt(n));
    } else if (strcmp(argv[1], "-a") == 0) {
	printf("abs(%d) is %.13f\n", n, absolute_value(n));
    } 
    else {
	usage();
    }

    return 0;
}
