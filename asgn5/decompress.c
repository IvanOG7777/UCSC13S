/*
* Program:      decompress
*
* Purpose:      Decompress a file that was compressed with "compress".
*
* Usage:        decompress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  decompress INFILE -o OUTFILE\n");
    exit(0);
}

/*
* Purpose:  To decompress items wihin a file.
*
* Parameters: Pass in a NIB pointer of type NIB and a FILE  pointer of type FILE
*
* Return: nothing (void)
*
*/

void decompress(NIB *nib, FILE *fout) { // pass in the nib pointer and file pointer
// while true
    while (1) {
	    // grab current nibble from nib and assign it to nibVal
        int nibVal = nib_get_nibble(nib);

        if (nibVal == EOF) { // if nib val reaches EOF
            break; // break early
        }

	// If nibVal is greater than 0, it represents one of the compressed codes.
        if (nibVal > 0) {
	// switch where we pass in the nibVal
        // and check the table of most common character to decompress
        // if nibVal is within the table
        // call fputc function and pass in its respective char and the file out pointer to print into the output file
            switch (nibVal) {
                case 1:
                    fputc(' ',  fout);
                    break;
                case 2:
                    fputc('e',  fout);
                    break;
                case 3:
                    fputc('t',  fout);
                    break;
                case 4:
                    fputc('n',  fout);
                    break;
                case 5:
                    fputc('r',  fout);
                    break;
                case 6:
                    fputc('o',  fout);
                    break;
                case 7:
                    fputc('a',  fout);
                    break;
                case 8:
                    fputc('i',  fout);
                    break;
                case 9:
                    fputc('s',  fout);
                    break;
                case 10:
                    fputc('d',  fout);
                    break;
                case 11:
                    fputc('l',  fout);
                    break;
                case 12:
                    fputc('h',  fout);
                    break;
                case 13:
                    fputc('c',  fout);
                    break;
                case 14:
                    fputc('f',  fout);
                    break;
                case 15:
                    fputc('p',  fout);
                    break;
                default:
                    break;
            };
        } else { // else if nibval isnt represented by table
	   //  make two nibbles
	   //  by calling nib_get_nibble and passing in nib to function
            int nibble1 = nib_get_nibble(nib);
            int nibble2 = nib_get_nibble(nib);

	    // check if nibble1 or nibble 2 are equal to EOF
	    // if so we return early from function
            if (nibble1 == EOF) {
                break;
            }

            if (nibble2 == EOF) {
                break;
            }

	    // create unsigned char nibbleByte
	    // left shift the lower 4 bits into high and only grab lower 4 bits from nibble2
	    // use bitwise OR to combine bits together into nibbleByte
            unsigned char nibbleByte = ((nibble1 & 0x0F) << 4) | (nibble2 & 0x0F);

            fputc(nibbleByte, fout); // use fputc to put this nibbleByte into the output file
        }
    }
}

int main(int argc, char **argv) {
	// check if we have passed in 4 arguments
    if (argc != 4) { // if not
        print_usage(); // print messege
        return 0; // return early from main
    }

    if (strcmp(argv[2], "-o") != 0) { // check if the third argument is not '-0'
        print_usage(); // print message
        return 0; // return early
    }

    char *inFile = argv[1]; // create char pointer called inFile will handle the name of the input file at argv[1]
    char *outFile = argv[3]; // create char pointer called outFile, will handle the name of the output file at argv[3]

    NIB *inFilePointer = nib_open(inFile, "r"); // create NIB pointer inFilePointer and assin the function call of nib_open where we pass in the inFile and file mode
    FILE *outFilePointer = fopen(outFile, "w"); // create FILE pointer outFilePointer and assign the function call of fopen where we pass in the outFile and file mode 

    // if the inputFilePointer is null print useage and return early
    if (inFilePointer == NULL) {
        return 0;
    }
    // if the outputFilePointer is null print usage and return early
    if (outFilePointer == NULL) {
        return 0;
    }
    // call the decompress function and pass in the inputFilePointer and outputFilePointer
    decompress(inFilePointer, outFilePointer);

    // close the nib pointer as well with nib_close function
    nib_close(inFilePointer);
    // once we finish close the inputFile pointer with fclose function
    fclose(outFilePointer);

    return 0;
}
