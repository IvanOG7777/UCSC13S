/*
* File:     nibbler.c
*
* Purpose:  Normally files are read and written one byte at a time, but
*           these routines let us read and write files one nibble (4 bits)
*           at a time.
*/

#include "nibbler.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Purpose:  Open a file for use by nib_get_nibble() or nib_put_nibble().
*
* Using fopen(), open file "filename" with mode "mode".
* If fopen() returns NULL, then this function returns NULL.
* Allocate a NIB struct using calloc(), and initialize it:
*
*    nib->underlying_f holds the return value from fopen().
*    nib->opened_for_read is set to 1 if mode starts with 'r'.
*
* Return a pointer to the NIB.
*/
NIB *nib_open(const char *filename, const char *mode) {
    FILE *filePointer = fopen(filename, mode); // create a FILE pointer call to the fopen function where we pass in the file name and the mode we want to enter the file in

    if (filePointer == NULL) { // if file filer pointer is null 
        return NULL; // return early from fucntion
    }

    NIB *nib = calloc(1, sizeof(NIB)); // create nib pointer of type NIB and allocate memory for one of size NIB using calloc
    assert(nib != NULL); // assert to check if memeory was reserved correctly

    nib->underlying_f = filePointer; // point to nib's underlying_f variable and set it to the current file pointer
    if (*mode == 'r') { // check if the mode is in reading
        nib->opened_for_read = 1; // set nib's opened_for_read to true by setting value to one
    }

    return nib; // return the nib pointer
}


/*
* Purpose:  Read a nibble from an open input file.
*
* if nib->num_nibbles > 0:
*    nib->num_nibbles = 0
*    Return nib->stored_nibble.
* else
*    int byte = fgetc(nib->underlying_f)
*    If byte is EOF then return EOF.
*    nib->stored_nibble = low nibble of the byte.
*    nib->num_nibbles = 1
*    Return high nibble of the byte.
*/
int nib_get_nibble(NIB *nib) {
    if (nib->num_nibbles > 0) { // check if we have an reaming nibbles within
	// if we do
        nib->num_nibbles = 0; // set the number of nibbles to 0
        return nib->stored_nibble & 0x0F; // return the nibs sotred remaining nibbles and make sure its only the lower 4 bits with 0X0F
    } else { // else if no stored nibble
        int b = fgetc(nib->underlying_f); // use fgetc to get the next unsinged char from nibs file pointer 
        if (b == EOF) return EOF; // once we react end of file we return EOF

        unsigned char byte = (unsigned) b; // create a unsigned char called byte and cast b to unsinged and assign to byte

        int high = (byte >> 4) & 0x0F; // right shift upper 4 bytes down to the lower ones and keep only the shifted bits and clear the upper ones by using & 0X0F
        int low = byte & 0x0F; // just keep the lower 4 bits by using & 0X0F

        nib->stored_nibble = low; // store the lower bits in nib's stored_nibble
        nib->num_nibbles = 1; // remember we have stores bits by setting num_nibbles to 1

        return high; // return the high bits
    }
}

/*
* Purpose:  Write a nibble to an open NIB.
*
* if nib->num_nibbles > 0:
*    Create a byte using nib->stored_nibble as the high nibble and the
*       parameter "nibble" as the low nibble.
*    Write the byte using fputc(nib->underlying_f).
*    nib->num_nibbles = 0
* else
*    nib->stored_nibble = nibble
*    nib->num_nibbles = 1
*/
void nib_put_nibble(int nibble, NIB *nib) {
    nibble &= 0x0F; // grab the lower 4 bits by using & 0X0F

    if (nib->num_nibbles > 0) { // check if passed nib has any stores bits
	// if it does
        int high = nib->stored_nibble & 0x0F; // pass in the stored bits make sure its only those bits with & 0X0F and make that our new high
        int low = nibble & 0x0F; // grab only the lower  4 bits with & 0X0F and make that our new low bits

        unsigned char byte = (high << 4) | low; // create an unsigned char called byte
						// left shift high by 4 btis to be upper of the byte
						// use | bitwise OR to combine the lower to form full byte
						// // assign to byte
        fputc(byte, nib->underlying_f); // use fputc function to then pass that new byte to the nib's FILE pointer
        nib->num_nibbles = 0; // set the number of nibbles to 0
    } else { // else if we dont have any nibbles
        nib->stored_nibble = nibble & 0x0F; // store the passed lower 4 bits of the passed nibble to stored nibble within nib
        nib->num_nibbles = 1; // remember that we have stored nibble by setting nun_nibbles to one
    }
}

/*
* Purpose:  Close the NIB file.
*
* If the file is opened for write and nib->num_nibbles > 0 then
*    create a byte with nib->stored_nibble as the high nibble.
*    write the byte using fputc(nib->underlying_f).
* Close file with fclose(nib->underlying_f).
*/
void nib_close(NIB *nib) {
    if (!nib->opened_for_read && nib->num_nibbles > 0) { // check if the isnt opend for reading AND the number of nibbles is greater than 0
        unsigned char byte = (unsigned char)((nib->stored_nibble & 0x0F) << 4); // create a unsigned char called byte
										// grab the lower 4 bits and left shift them to be higher 4 bits
										// cast to unisgned char and assign to byte

        fputc(byte, nib->underlying_f); // using fputc pass that byte to the curretn FILE pointer in nib
    }

    fclose(nib->underlying_f); // once we finish close the file
}
