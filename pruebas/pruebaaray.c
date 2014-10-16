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
char *p = "manchatasiiiiiiiiiiii";
char array[a][b];

	int i;
	int j;
	int k = 0;
	for (i = 0; i < a; i++)
	{
		for(j = 0; j< b; j++)
		{	
			array[i][j] = *(p+(k++));
			printf("%c", array[i][j]);
		}
		printf("\n");
	}

	printf("\nsize:%zu, %s\n",strlen(array[2]), array[2]);

	// int array2[3][2] = {{1,2},{3,4},{5,6}};

	// for (i = 0; i < 3; i++)
	// {
	// 	for(j = 0; j< 2; j++)
	// 	{	
	// 		//array[i][j] = ++k;
	// 		printf("%d", array2[i][j]);
	// 	}
	// 	printf("\n");
	// }



	
}