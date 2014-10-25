#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *mystrtok(char *s, char tok);

int main()
{
	char *prueba = "esto:es:prueba";

	char *s1 = mystrtok(prueba, ':');
	char *s2 = mystrtok(prueba, ',');

	printf("s1: %s\ns2: %s\n",s1,s2);

    return 0;
}
char *mystrtok(char *s, char tok)
{
    char *token, *res, *temp;

    if((token = strchr(s, tok)) == NULL){return s;} //token not found

    size_t len = token - s;
    temp = malloc(len + 1);
    memcpy (temp,s,len);
    temp[len] = '\0';
    res = temp;

    return res;
}