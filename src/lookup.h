#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);


struct nlist {		/* table entry: */
struct nlist *next;	/* next entry in chain */
char *name;			/* defined name */
char *defn;			/* replacement text */
};