struct montoto
{
	int n_arg;
	// char *entry;
	// char **arg;
};

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 512

int main(int argc, char *argv[])
{
const int a = 3;
const int b = 3;
int array[a][b];

	int i;
	int j;
	int k = 0;
	for (i = 0; i < a; i++)
	{
		for(j = 0; j< b; j++)
		{	
			array[i][j] = ++k;
			printf("%d", array[i][j]);
		}
		printf("\n");
	}

	printf("\n%d\n",*(array[2] + 1));

	
}