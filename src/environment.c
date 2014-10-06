#include "headers.h"
#include "environment.h"


void runenv(struct ptype *env)
{
	while(1)
		{
			// env->n_arg = 1;   //initialized to 1 by default, it updates later
			// printf("asigna 1 al entero\n");

			 // printf("entra al while\n");

			 env->entry = malloc(MAXSIZE);
			 // printf("hace el malloc\n");


			printf("emul-mips>"); // prints out the prompt
			
			char *result = fgets(env->entry,MAXSIZE,stdin);  // obtiene la env->entry por teclado
			if (result == NULL)
			{
				printf("\n");     //si la env->entry da error o indica condicion de EOF, el programa termina
				exit(0);
			}
			env = parseentry(env);													

			analize(env);  /** el hijo analiza el comando y lo ejecuta si existiere**/	 
			restart(env);	/** reinicia env->arg para que no quede con residuos a la hora de analizar un nuevo comando**/
		}
}

/**
*@brief this function sets to null the values in command and in arg array
*
* it just to reset and prepare the variables for the next command
**/
void restart(struct ptype *env)
{		
	env->command = NULL;
	int i;
	for (i = 0; i<env->n_arg;i++)
		env->arg[i] = NULL;
}



struct ptype *parseentry(struct ptype *env)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;
    env->n_arg = 1; //initialized to 1 by default, it updates later if there are any arguments

	 // printf("env->entry: '%s'\n",env->entry);

	//and now we parse	
    env->command = strtok(env->entry, " ");
    strip(env->command);

    //the rest of the string remaining in buffer are the arguments. so we continue parsing
    int i = 0;
    while ((buffer = strtok(NULL, " ")) != NULL)
    {	
        env->arg[i] = buffer;
        i++;
    }
    env->n_arg = i;

	for(i = 0; i < env->n_arg; i++)
	strip(env->arg[i]);   

	return env;
}


void analize(struct ptype *env)
{

	if(!strcmp(env->command,"exit"))
    {
    	printf("exiting mips emulator...\n");
    	exit(0);   
    }
	else if(!strcmp(env->command,"load"))
	{
		printf("load was entered...\n");
	}
	else if(!strcmp(env->command,"disp"))
	{
		printf("disp was entered...\n");
	}
	else if(!strcmp(env->command,"disasm"))
	{
		printf("disasm was entered...\n");
	}
	else if(!strcmp(env->command,"set"))
	{
		printf("set was entered...\n");
	}
	else if(!strcmp(env->command,"assert"))
	{
		printf("assert was entered...\n");
	}
	else if(!strcmp(env->command,"debug"))
	{
		printf("debug was entered...\n");
	}
	else if(!strcmp(env->command,"resume"))
	{
		printf("resume was entered...\n");
	}
	else if(!strcmp(env->command,"run"))
	{
		printf("run was entered...\n");
	}
	else if(!strcmp(env->command,"step"))
	{
		printf("step was entered...\n");
	}
	else if(!strcmp(env->command,"break"))
	{
		printf("break was entered...\n");
	}
	else printf("command '%s' not found\n",env->command);

}

/**esta funcion descarta cualquier \0, \t, o \n que pueda ser encontrado dentro de un puntero a caracter**/
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