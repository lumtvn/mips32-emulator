struct nlist {		/* table entry: */
struct nlist *next;	/* next entry in chain */
char *name;			/* defined name */
char *defn[];			/* replacement text */
};

#define HASHSIZE 101
#define TYPES 2
static struct nlist *hashtab[TYPES][HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);

