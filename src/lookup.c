/**
*@file lookup.c
*@author Dennis Ritchie and Brian Kernighan
*@brief functions taken from the book "C Programming", by Dennis Ritchie and Brian Kernighan.
*@see for more information about lookup: http://zanasi.chem.unisa.it/download/C.pdf 
**/

#include "lookup.h"
#include "headers.h"

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
			/* found */
		return NULL;
		/* not found */
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
		if ((np = lookup(name)) == NULL)  /* not found */
			 {
				np = (struct nlist *) malloc(sizeof(*np));
					if (np == NULL || (np->name = strdup(name)) == NULL)
					return NULL;
				hashval = hash(name);
				np->next = hashtab[hashval];
				hashtab[hashval] = np;
		 	 } 
		else
			/* already there */
			free((void *) np->defn);
			/*free previous defn */
			if ((np->defn = strdup(defn)) == NULL)
			return NULL;
			return np;
}

int undef(char * name) {
    struct nlist * np1, * np2;

    if ((np1 = lookup(name)) == NULL)  /*  name not found  */
        return 1;

    for ( np1 = np2 = hashtab[hash(name)]; np1 != NULL;
          np2 = np1, np1 = np1->next ) {
        if ( strcmp(name, np1->name) == 0 ) {  /*  name found  */

            /*  Remove node from list  */

            if ( np1 == np2 )
                hashtab[hash(name)] = np1->next;
            else
                np2->next = np1->next;

            /*  Free memory  */

            free(np1->name);
            free(np1->defn);
            free(np1);

            return 0;
        }
    }

    return 1;  /*  name not found  */
}