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
struct ptype *parse(struct ptype *data){

	char *buffer;
	char *temp;

	printf("%s\n",data);

	buffer = strtok(data->incoming_line, "#"); // we temporarely put the incoming line into a buffer to get rid of the commentaries

	printf("asigna incoming_line a buffer sin drama: %s\n", buffer);
	//and now we parse	
    temp = strtok(buffer, " ");

    //at this moment, temp holds either a tag or the comment. 
    if(temp[0] == '.')
    	{
    		data->tag = temp; //if the first caracter of temp is a dot ".", then its a tag
    		data->operation = strtok(NULL, " "); // and the second string is the operation
    	}
    else data->operation = temp; //if it's not, then it has to be the operation


   	//the rest of the string remaining in buffer are the arguments. so we continue parsing
    int i = 0;
    while (temp = strtok(buffer, " ") != NULL && i < 4)
    {
    	data->arg[i] = temp;
    	i++;
    }





	return data;
}