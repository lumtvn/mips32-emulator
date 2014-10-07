#include <lookup.h>

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
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s, struct nlist *hashtablocal[HASHSIZE])
{
	struct nlist *np;
	for (np = hashtablocal[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
			/* found */
		return NULL;
		/* not found */
}

struct nlist *newinstall(char *name, char *defn, int type)
{
	struct nlist *np;
	np = install(name, defn, hashtab[type]);
}

struct nlist *install(char *name, char *defn, struct nlist *hashtablocal[HASHSIZE])
{
	struct nlist *np;
	unsigned hashval;
		if ((np = lookup(name, hashtablocal)) == NULL)  /* not found */
			 {
				np = (struct nlist *) malloc(sizeof(*np));
					if (np == NULL || (np->name = strdup(name)) == NULL)
					return NULL;
				hashval = hash(name);
				np->next = hashtablocal[hashval];s
				hashtablocal[hashval] = np;
		 	 } 
		else
			/* already there */
			free((void *) np->defn);
			/*free previous defn */
			if ((np->defn = strdup(defn)) == NULL)
			return NULL;
			return np;
}