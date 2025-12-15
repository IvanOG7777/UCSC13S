#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

// main function passes in the argument count and string of arguments
int main(int argc, char **argv) {

    // declare file descriptor of type int
    int fd;

    if (argc == 1) { // no file name
        fd = STDIN_FILENO; // read from the keyboard or pipe
    } else if (argc == 2) { // file name passed
        fd = open(argv[1], O_RDONLY); // open file in 0_RDONLY pass hex val to fd
        if (fd < 0) {// if fd produces a negative number (failure)
            return 1; // return 1 as a program failure
        }
    } else { // if argc has too many arguments
        return 1;
    }

    unsigned char buffer[16]; // create buffer of unsigned char, assign enough space for 16 bytes
    size_t offset = 0; // create by offset counter.

    // while true
    while (1) {
        ssize_t filled = 0; // create filled variable to track how many bytes have been read into the buffer

        // while the filled bytes is less than 16 keep filling
        while (filled < 16) {

            // read bytes from the input into the buffer, starting at the first empty position
            // depending on how many have been filled we will wil read for buffer + filled bytes in and 16 - filled of remaining space
            ssize_t n = read(fd, buffer + filled, 16 - filled);

            // if n is less than 0
            if (n < 0) {
                // if file opened is a real file close it
                // if program is reading from stdin don't close it
                if (fd != STDIN_FILENO) {
                    close(fd);
                }
                return 1;
            }

            // stop reading as we have reached EOF
            if (n == 0) {
                break; // break out if second while loop
            }

            // add number of bytes read from n into filled
            filled += n;
        }

        // if no bytes were read, no more data to process
        if (filled == 0) {
            break; // break out of main while loop
        }

        // print the offset using 8 digit hex number
        printf("%08zx: ", offset);

        // for loop to loop through the 16 positions
        for (int i = 0; i < 16; i++) {
            if (i < filled) printf("%02x", buffer[i]); //if current index is smaller that filled print the buffer byte at i using 2 digit hex value
            else
                printf("  "); // else print a double space
            if (i % 2 == 1) printf(" "); // if i % 2 is equal to 1 print a single space
        }

        printf(" "); // print space

        //for loop to print the ascii representation of the current byte
        // from 0 -> filled
        for (int i = 0; i < filled; i++) {
            unsigned char c = buffer[i]; // assign unsigned char c to the current buffer byte at index i
            if (isprint(c)) { // check if c is printable
                printf("%c", c); // print the character
            } else { // else
                printf("."); // print the '.'
            }
        }

        // print an end line
        printf("\n");

        offset += filled;
    } //end of while(1)

    // check if we opened a real file or if its keyboard input
    if (fd != STDIN_FILENO) { // if  fd isn't a stdin then it must be a real file
        if (close(fd) < 0) { // if the closing of the file produces a negative number (failure to close)
            return 1; // return 1 as a failed program
        }
    }

    return 0;
}
