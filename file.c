#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "wav.h"
#include <errno.h>

/*********************************************************************
* The class that handles the work of data flowing in into the buffer
 * and out from the buffer
*
* @author Logan Jaglowski
* @version Winter 2020
* ******************************************************************/

/*********************************************************************
 * The method that reads the file itself into the buffer.
 *
 * @param filename the name of the file
 * @param buffer the buffer that the file will read into
 * @returns size_t the size of the file
 ********************************************************************/
size_t read_file( char* filename, char **buffer ) {
    // open a new file
    FILE *out = fopen(filename, "rb");

    // if file can't be opened, an error is shown.
    if (out == NULL) {
        printf("Failed to open file: %u\n", errno);
    }

    // get the entire size of the file
    fseek(out, 0, SEEK_END);
    long size = ftell(out);
    fseek(out, 0, SEEK_SET);

    // allocate enough memory to the buffer to store the size
    *buffer = malloc(size+1);

    // read the file into the buffer
    fread(*buffer, 1, size, out);

    // close the file and return the size
    fclose(out);
    return size;
}

/*********************************************************************
 * The method that writes the new file from the buffer.
 *
 * @param filename the name of the new file
 * @param buffer the buffer that will pass data into the file
 * @param size the size of the file
 * @returns size_t the size of the file
 ********************************************************************/

size_t write_file( char* filename, char *buffer, size_t size) {

    // create a wav_file struct to easily track info about the file
    wav_file *easyFile = (wav_file *) buffer;

    // variables for the loop
    long start = 44;
    long finish = size - 2;

    // a loop going from start to end reversing the entire file
    while (start < finish) {
        char keep = buffer[start];
        buffer[start] = buffer[finish];
        buffer[finish] = keep;
        start++;
        finish--;
    }

    // a loop going from start to finish, ensuring the samples
    // stay in the same order
    for(int i = 44; i < size - 2; i+=(easyFile->BitsPerSample/8)) {
        int s = (easyFile->BitsPerSample/8);
        int j = 0;
        while (j < s) {
            char keep = buffer[i + j];
            buffer[i + j] = buffer[i + s];
            buffer[i + s] = keep;
            s--;
            j++;
        }
    }

    // opening the new file to put the data into
    FILE *open = fopen(filename, "w");

    // provides an error message if the file can't be opened
    if (open == NULL) {
        printf("Failed to open file: %u\n", errno);
    }

    // buffer is written into the file
    fwrite(buffer, 1, size, open);

    // file is closed, size is returned
    fclose(open);
    return size;
}
