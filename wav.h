#ifndef WAV_H_INCLUDED
#define WAV_H_INCLUDED

/*********************************************************************
* The class that parses the buffer into a wav_file construct
*
* @author Logan Jaglowski
* @version Winter 2020
********************************************************************/

// the struct that carries the data and allows the user to read file
// data easier
typedef struct wav_files {
    char riff[4];
    int chunkSize;
    char wave[4];
    char format[4];
    int formatLength;
    short formatType;
    short numChannels;
    int sampleRate;
    int byteRate;
    short blockAlignment;
    short BitsPerSample;
    char data[4];
    int dataSize;
    char totalData[];
} wav_file;

wav_file* parse(char* contents);

#endif // WAV_H_INCLUDED
