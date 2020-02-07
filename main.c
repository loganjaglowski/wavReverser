#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"
#include "file.h"

/*********************************************************************
 * A program that reverses wav files based of the data inside of them
 *
 * @author Logan Jaglowski
 * @version Winter 2020
 * ******************************************************************/

/*********************************************************************
 * The main method that dictates the order in which the file is read
 * and then written
 *
 * @param argc counts the number of arguments given
 * @param argv all of the arguments given from the user
 * @returns int will tell the user if the program exited correctly
 ********************************************************************/

int main(int argc, char **argv) {
    /** the main buffer that will be used throughout the program */
    char *mainBuffer;

    // reading the file into the buffer
    size_t size = read_file(argv[1], &mainBuffer);

    // parsing the buffer
    parse(mainBuffer);

    // creating a wav_file struct to extract data
    wav_file *output = (wav_file *) mainBuffer;
    char w = output->wave[0];
    char a = output->wave[1];
    char v = output->wave[2];
    char e = output->wave[3];

    // ensuring that this is a wave file
    if (w != 'W') {
        printf("The inputted file is not a wav file. Program failed.");
        return -1;
    }
    if (a != 'A') {
        printf("The inputted file is not a wav file. Program failed.");
        return -1;
    }
    if (v != 'V') {
        printf("The inputted file is not a wav file. Program failed.");
        return -1;
    }
    if (e != 'E') {
        printf("The inputted file is not a wav file. Program failed.");
        return -1;
    }

    //outputting file statistics from the struct
    printf("%s%s\n", "File: ", argv[1]);
    printf("========================\n");
    printf("%s%u\n", "File size is ", output->chunkSize);
    printf("%s%s%s%u\n", "Format is ", output->format,
        "with format data length ", output->formatLength);
    printf("%s%s\n", "Format type is ", output->wave);
    printf("%u%s%u\n", output->numChannels,
        " channels with a sample rate of ", output->sampleRate);
    printf("%u%s\n", output->byteRate, " byte rate");
    printf("%u%s\n", output->blockAlignment, " alignment");
    printf("%u%s\n", output->BitsPerSample, " bits per sample");
    printf("%s%s\n", output->data, " is data");
    printf("%u%s\n", output->dataSize, " is the data size");

    // writing the new file with the buffer and new given name
    write_file(argv[2], mainBuffer, size);

    //freeing the buffer
    free(mainBuffer);

    //program exits error free
    return 0;
}
