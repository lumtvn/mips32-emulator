/**
 * @file interpreter.c
 * @author Luciano Mantovani
 * @date December 2014
 * @brief file containing functions used by main to parse and interpretate the line entered by user
 *
 * this file blablablablalba
 * 
 * 
 */
#include "headers.h"
#include "interpreter.h"


/**
*
*@brief this function parses the line entered by user and identifies the tag, the operation, the arguments, and gets rid of the commentaries
*
*
*
*/
struct ptype *parse(struct ptype *data)
{

	char *buffer1;
	char *buffer2;
    char *temp1;
    char *temp2 = NULL;

	// printf("data->incoming_line: '%s'\n",data->incoming_line);

	buffer1 = strtok(data->incoming_line, "#"); // we temporarely put the incoming line into a buffer1 to get rid of the commentaries
	
	// printf("buffer1: '%s'\n", buffer1);
	//and now we parse	
    buffer2 = strtok(buffer1, " ");

    // printf("buffer2: '%s'\n",buffer2);

    //at this moment, buffer2 holds either a tag, a label or the operation. 
    //if it holds a label, then buffer2 has a double colon at the end. we locate this using strchr()

    temp1 = strchr(buffer2, ':');
    if(temp1) //this is here in case strchr returns null, in which case there is no label
        {
            size_t len = temp1 - buffer2;
            temp2 = malloc(len + 1);
            memcpy(temp2,buffer2,len);
            temp2[len] = '\0';
            //now temp2 has the label
            data->label = temp2;
            buffer2 = strtok(NULL, " "); // and then we load the second string of buffer1 to buffer2
        }

        // now we search for the tag
    if(buffer2[0] == '.')
        {
            data->tag = buffer2; //if the first or second character of buffer2 is a dot, then its a tag
            data->operation = strtok(NULL, " "); //and then follows the command.
        }
    else    data->operation = buffer2; //if it's not a tag or a label, then it has to be the operation

    //the rest of the string remaining in buffer1 are the arguments. so we continue parsing
    int i = 0;
    while ((buffer2 = strtok(NULL, " ")) != NULL && i < 4)
    {
        data->arg[i] = buffer2;
        i++;
    }

    //we proceed to clean the commas out of the arguments. It had to be done separatedly from the
    //previous while becouse if not, strtok doesn't work correctly

    i = 0;
     while ((buffer2 = strtok(data->arg[i], ",")) != NULL || i < 4)
    {
    	data->arg[i] = buffer2;
    	 i++;
    }

    // printf("data->tag: '%s'\n", data->tag);
    // printf("data->label: '%s'\n", data->label);
    // printf("data->operation: '%s'\n", data->operation);
    // printf("data->arg[0]: '%s'\n", data->arg[0]);
    // printf("data->arg[1]: '%s'\n", data->arg[1]);
    // printf("data->arg[2]: '%s'\n", data->arg[2]);
    // printf("data->arg[3]: '%s'\n", data->arg[3]);

   // free(temp2);



	return data;
}


struct ptype *readscript(struct ptype *data)
{

    static const char filename[] = "./test/testscript.elf";

    FILE *file = fopen ( filename, "r" );

    size_t filesize;
    fseek(file, 0, SEEK_END); // seek to end of file
    filesize = ftell(file); // get current file pointer
    fseek(file, 0, SEEK_SET); // seek back to beginning of file



    if ( file != NULL )
        {
            char line [ 128 ]; /* or other suitable maximum line size */
            while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
                {
                    fputs ( line, stdout ); /* write the line */
                }
            fclose ( file );
        }
    else
        {
            perror ( filename ); /* why didn't the file open? */
        }
    

    return 0;
}
