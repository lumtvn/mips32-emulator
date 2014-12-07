#include "headers.h"

/* push: push f onto value stack */
void push(struct ptype *mips, word f)
{
	if (mips->sp < STACKSIZE)
		mips->stack[mips->sp++] = f;
	else
		printf("error: stack full, can't push 0x%x\n", f);
}
/* pop: pop and return top value from stack */
word pop(struct ptype *mips)
{
	if (mips->sp > 0)
		return mips->stack[--mips->sp];
	else 
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}
