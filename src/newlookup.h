struct nlist {		/* table entry: */
struct nlist *next;	/* next entry in chain */
char *name;			/* defined name */
char *defn[];			/* replacement text */
};

#define HASHSIZE 101
#define TYPES 2
static struct nlist *hasharray[TYPES];
static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s, struct nlist *hashtablocal[HASHSIZE]);
struct nlist *install(char *name, char *defn[], int defns, struct nlist *hashtablocal[HASHSIZE]);
struct nlist *newlookup(char *s, int type);
struct nlist *newinstall(char *name, char *defn[], int defns, int type);