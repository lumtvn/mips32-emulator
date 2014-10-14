#include "headers.h"
#include "environmentcommands.h"
#include "assembler.h"

struct ptype *load(struct ptype *env)
{
	if(env->arg[1] != NULL)
		{
			env->filename = env->arg[1];
			env = compile(env);
			return env;
		}
	else return env;
}
