#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

/*********************************************************************
* The class that handles the work of data flowing in into the buffer
 * and out from the buffer
*
* @author Logan Jaglowski
* @version Winter 2020
* ******************************************************************/

size_t read_file( char* filename, char **buffer );

size_t write_file( char* filename, char *buffer, size_t size);

#endif // FILE_H_INCLUDED
