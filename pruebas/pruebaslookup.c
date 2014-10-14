#include <stdlib.h>
#include <stdio.h>
#include "../src/lookup.c"

int main(int argc, char *argv[])
{
	char *a,*b,*c;
	struct nlist *na,*nb,*nc,*nr;

	a = "hola";
	b = "como";
	c = "andas";

	ha = hash(a);
	hb = hash(b);
	hc = hash(c);

	na = newinstall(a, "soyhola");
	nb = newinstall(b, "soycomo");
	nc = newinstall(c, "soyandas");

	nr = newlookup(a);
	printf("a, con name '%s', tiene un defn '%s'\n",na->name,na->defn);

	nr = newlookup(b);
	printf("b, con name '%s', tiene un defn '%s'\n",nb->name,nb->defn);

	nr = newlookup(c);
	printf("c, con name '%s', tiene un defn '%s'\n",nc->name,nc->defn);


	return 0;
}