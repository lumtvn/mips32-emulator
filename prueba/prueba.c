#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strang(char *s);

int main()
{
    char *s;
    s = malloc(10 * sizeof(char));
    strcpy(s,"OP_");
    strcat(s,"ADD");

    printf("%s\n",s);

    free(s);
    
    return 0;
}
int strang(char *s)
{
    char *s1;

    if((s1 = strtok(s, " ")) != NULL)
    {
    printf("s1: %s\n string ingresado: %s\n",s1,s);
    }

    return 0;
}