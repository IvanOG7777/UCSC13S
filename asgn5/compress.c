/*
* Program:      compress
*
* Purpose:      Compress a file.
*
* Usage:        compress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  compress INFILE -o OUTFILE\n");
    exit(0);
}

/*
* Purpose:  To compress items wihin a file.
*
* Parameters: Pass in a file pointer of type FILE and a nib pointer of type NIB
*
* Return: nothing (void)
* 
*/
void compress(FILE *fin, NIB *nib) {// pass in both FILE and NIB pointers
	// while true
	while (1) {
	// keep grabbing each characrter from the  file 
        int ch = fgetc(fin); // by using fgetc
	// until we reach the EOF
        if (ch == EOF) {
            break; // break out of loop
        }

        unsigned char byte = (unsigned char) ch; // create unsinged char called byte
						 // cast the current char from file to unisgned char and assign to byte

	// switch where we pass in the byte
	// and check the table of most common character to compress
	// if byte is within the table 
	// call nib_put_nibble and pass in its respective number and current nib pointer
        switch (byte) {
            case ' ':
                nib_put_nibble(1, nib);
                break;
            case 'e':
                nib_put_nibble(2, nib);
                break;
            case 't':
                nib_put_nibble(3, nib);
                break;
            case 'n':
                nib_put_nibble(4, nib);
                break;
            case 'r':
                nib_put_nibble(5, nib);
                break;
            case 'o':
                nib_put_nibble(6, nib);
                break;
            case 'a':
                nib_put_nibble(7, nib);
                break;
            case 'i':
                nib_put_nibble(8, nib);
                break;
            case 's':
                nib_put_nibble(9, nib);
                break;
            case 'd':
                nib_put_nibble(10, nib);
                break;
            case 'l':
                nib_put_nibble(11, nib);
                break;
            case 'h':
                nib_put_nibble(12, nib);
                break;
            case 'c':
                nib_put_nibble(13, nib);
                break;
            case 'f':
                nib_put_nibble(14, nib);
                break;
            case 'p':
                nib_put_nibble(15, nib);
                break;
            default:
		// if the current byte instn in this table
		// call nib_put_nibble with default 0 int and the current nib pointer 
                nib_put_nibble(0, nib);

                int high = (ch >> 4) & 0x0F; // grab the current char from file right shift it 4 bits and only grab the upper bits y using & 0X0f
                int low = ch & 0x0F; // grab only the lower 4 bits by using & 0X0F

		// call the nib_put_nibble function
		// and pass in the high and low along with nib pointer for both
                nib_put_nibble(high, nib);
                nib_put_nibble(low, nib);
        };
    }
}

int main(int argc, char **argv) {
	// check if we have passed in 4 arguments
    if (argc != 4) { // if not
        print_usage(); // print messege
        return 0; // return early from main call
    }

    if (strcmp(argv[2], "-o") != 0) { // check if the third argument is not '-0'
	print_usage(); // print messege
        return 0; // return early
    }

    char *inFile = argv[1]; // create char pointer called inFile will handle the name of the input file at argv[1]
    char *outFile = argv[3]; // create char pointer called outFile, will handle the name of the output file at argv[3]

    FILE *inputFilePointer = fopen(inFile, "r"); // use fopen on the inFile and open file in reading mode and set it to a FILE pointer inputFilePointer
    NIB *outPutFilePointer = nib_open(outFile, "w"); // create NIB pointer outPutfilePointer and call nib_open function and pass in the outFile and w for writing mode 
   
    // if the inputFilePointer is null print useage and return early
    if (inputFilePointer == NULL) {
        print_usage();
	return 0;
    }
    // if the outputFilePointer is null print usage and return early
    if (outPutFilePointer == NULL) {
        print_usage();
	return 0;
    }

    // call the compress function and pass in the inputFilePointer and outputFilePointer
    compress(inputFilePointer, outPutFilePointer);

    // once we finish close the inputFile pointer with fclose function
    fclose(inputFilePointer);
    // close the nib pointer as well with nib_close function
    nib_close(outPutFilePointer);

    return 0;
}
