/**
 * @file reader.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions used by main to read a new elf script
 *
 * This file has functions called by the main program when it has to read a new elf script. 
 * The reading of a new file, includes also the removal of the commentary.
 *
 * the only parameter taken in this and in every function in all source files is a pointer
 * to a struct data type. It makes it easier to handle information between functions.
 *
 **/
#include "headers.h"
#include "reader.h"

/**
*
*@brief this function reads an incoming script, and removes the commentary from it
*@param *data A pointer to a ptype structure, created by the main program.
*@return it returns the same structure, but with data->full_script modified(it now has the script, with the commentaries striped)
*@todo the size of the string that holds the entire file should be modified when once the commentaries are removed
*@errorcode 100 -> 109
*/
struct ptype *readscript(struct ptype *data)
{   
    FILE *file;
    if((file = fopen ( data->filename, "r" )) == NULL)
    {
        data->report = 100;
        return data;
    }

    size_t filesize;
    fseek(file, 0, SEEK_END); // seek to end of file
    filesize = ftell(file); // get current file pointer
    fseek(file, 0, SEEK_SET); // seek back to beginning of file

    data->full_script = malloc(filesize);

            char *line = malloc(MAXSIZE);

            while ( fgets ( line, MAXSIZE, file ) != NULL ) /* read a line */
                {
                    line = removecommentary(line);
                    strcat(data->full_script,line);
                }
            fclose ( file );

    data->report = 0;
    return data;
}

/**
*@brief this function simply removes the commentary from a char * using the string function "strchr"
*
*
*
*
*@todo: this doesn't contemplate yet the case in which there's a # character surrounded by commas ""
*/
char *removecommentary(char *s)
{   
    char *temp1;
    char *temp2;

    temp1 = strchr(s,'#');

    if(temp1) // if temp1 isn't null, then there's a commentary in this line
        {
            size_t len = temp1 - s;
            temp2 = malloc(len + 1);
            memcpy(temp2,s,len);
            temp2[len] = '\0';
            //now temp2 has the line without the commentary
            return temp2;
        }
   
    else    return s; //if strchr returns null, there's nothing to do   
}
    