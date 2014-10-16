#include "headers.h"
#include "environmentcommands.h"
#include "assembler.h"
#include "errors.h"

struct ptype *env_load(struct ptype *env)
{
	if(env->argenv[0] != NULL)
		{
			env->filename = env->argenv[0];
			printf("trying to compile file: '%s'\n", env->filename);
			env = compile(env);
			return env;
		}
	else return env;
}

struct ptype *env_set(struct ptype *env)
{
	if(!strcmp(env->argenv[0],"mem"))
		{
			printf("set mem was entered\n");
			env->report = 0;
		}
	else if(!strcmp(env->argenv[0], "reg"))
		{
			printf("set reg was entered\n");
			env->report = 0;
		}
	else env->report = 2;


}
