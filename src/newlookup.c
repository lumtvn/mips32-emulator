#include "headers.h"
#include "newlookup.h"

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}


struct nlist *newlookup(char *s, int type)
{
	struct nlist *np;
	np = lookup(s, hashtab[type]);

	return np;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s, struct nlist *localhashtab[HASHSIZE])
{
	struct nlist *np;
	for (np = localhashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
			/* found */
		return NULL;
		/* not found */
}

struct nlist *newinstall(char *name, char *defn[], int defns, int type)
{
	struct nlist *np;
	np = install(name, defn, defns, hashtab[type]);

	return np;
}

struct nlist *install(char *name, char *defn[], int defns, struct nlist *localhashtab[HASHSIZE])
{
	struct nlist *np;
	unsigned hashval;
		if ((np = lookup(name, localhashtab)) == NULL)  /* not found */
			 {
				np = (struct nlist *) malloc(sizeof(*np));
					if (np == NULL || (np->name = strdup(name)) == NULL)
					return NULL;
				hashval = hash(name);
				np->next = localhashtab[hashval];
				localhashtab[hashval] = np;
		 	 } 
		else
			/* already there */
			free((void *) np->defn);
			/*free previous defn */
			int i;
			for (i = 0; i < defns; i++)
			{
				if ((np->defn[i] = strdup(defn[i])) == NULL) //all defn arrays should have at least 1 argument
				return NULL;
				return np;
			}
}