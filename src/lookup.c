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