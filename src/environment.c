/**
 * @file environment.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions to run the environment for the user
 *
 * this file has functions that react to the lines entered by the user. The commands from the
 * file environmentcommands.c are called by functions from this file.
 **/
#include "headers.h"
#include "environment.h"
#include "environmentcommands.h"
#include "errors.h"


/**
*@brief this function runs the environment program and allows the user to enter commands
*
* after obtaining a line from stdin, it parses it and analizes the command. The function
* analize() also executes it, and if there's no report (mips->report = 0) the program leaves.
*F
*@note this function is thought to be called within an endless loop
**/
int runenv(struct mipsstr *mips)
{
	mips->breakpoints[0] = 0xFFFFFFFF;
	mips->fl_step_into = false;

	// printf("emul-mips>"); // prints out the prompt
	
	 mips->entry = readline("emul-mips> ");
            
    if (mips->entry == NULL)
    {
        printf("\n");    
        exit(0);
    }
    add_history(mips->entry);


	if (strlen(mips->entry) > 1)
	{
		mips = parseentry(mips);													
		mips = analize(mips); 

		if(mips->report != 0)
			report(mips->report);
		mips->report = 0;

		restart(mips);
	}

	return 0;
}

/**
*@brief this function sets to null the values in command and in argenv array
*
* it just to reset and prepare the variables for the next command
**/
void restart(struct mipsstr *mips)
{		
	// mips->command = NULL;
	int i;
	for (i = 0; i<mips->n_argenv;i++)
		mips->argenv[i] = NULL;
}


/**
*@brief this function parses an entry in the environment
*
* it parses the entire line entered and stores the command in the field char *command from the struct 
* mipsstr, and stores all the arguments in the field char *argenv[] from the structure mipsstr
*
**/
struct mipsstr *parseentry(struct mipsstr *mips)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;
    mips->n_argenv = 1; //initialized to 1 by default, it updates later if there are any arguments

	//and now we parse	
    mips->command = strtok(mips->entry, " ");
    strip(mips->command);

    //the rest of the string remaining in buffer are the arguments. so we continue parsing
    int i = 0;
    while ((buffer = strtok(NULL, " ")) != NULL)
    {	
        mips->argenv[i] = buffer;
        i++;
        if(i == 32)
        {
        	/*array cant hold more than 32 arguments. operation failed*/
        	return mips;
        }
    }
    mips->n_argenv = i;

	for(i = 0; i < mips->n_argenv; i++)
	strip(mips->argenv[i]);


	return mips;
}

/**
*@brief this function is a distributer, it calls a function from file environmentcommands.c according to the command entered in the entry
*
* 
* the only command that doesn't call any function is exit
* 
* @todo debug and resume function
**/
struct mipsstr *analize(struct mipsstr *mips)
{

	if(!strcmp(mips->command,"exit"))
    {
    	printf("exiting mips emulator...\n");
    	mips->fl_exit = true;
    	mips->report = 0;
    	return mips;
    }
	else if(!strcmp(mips->command,"load")){ mips = env_load(mips); return mips;}

	else if(!strcmp(mips->command,"disp"))	{	mips = env_disp(mips); return mips;}

	else if(!strcmp(mips->command,"disasm")){	mips = env_disasm(mips); return mips;}

	else if(!strcmp(mips->command,"set"))	{	mips = env_set(mips); return mips;}

	else if(!strcmp(mips->command,"assert")){	mips = env_assert(mips); return mips;}

	else if(!strcmp(mips->command,"debug"))	{	printf("debug was entered...\n"); return mips;}

	else if(!strcmp(mips->command,"resume")){	printf("resume was entered...\n");return mips;}

	else if(!strcmp(mips->command,"run"))	{	mips = env_run(mips); return mips;}

	else if(!strcmp(mips->command,"step"))	{	mips = env_step(mips); return mips;}

	else if(!strcmp(mips->command,"break"))	{	mips = env_break(mips); return mips;}

	else printf("command '%s' not found\n",mips->command);

	return mips;

}

/**
*@brief this function simply discards unwanted characters in a string
*
*@param char *s the string to be stripped
*@return void there's no need to return a value since we are working with pointers
*/
void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
    	if(*s != '\t' && *s != '\n') {
    		*p2++ = *s++;
    	} else {
    		++s;
    	}
    }
    *p2 = '\0';
}
