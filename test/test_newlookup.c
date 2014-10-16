#include "../src/headers.h"
#include "../src/newlookup.h"
#include "minunit.h"

 int tests_run = 0;
 int res;
 struct nlist nna;
 struct nlist *na = &nna;
 char *a = "hello";
 char *b = "foo";
 char *defna[2] = {"world","programmers"};
 int defnsa = 2;

/*tries to newinstall a defn in a non existing name*/
  static char * test_newinstall_create() 
{ 
			na = newinstall(a,defna,defnsa,0);
      printf("%s, %s, %s\n", na->name, na->defn[0], na->defn[1]);
            mu_assert("newinstall non existing name", !strcmp(na->name,"hello") && !strcmp(na->defn[0],"world") && !strcmp(na->defn[1],"programmers"));
      printf("hace el assert\n");
            return 0;
}

/*tries to overwrite a defn in an existing name*/
  static char * test_newinstall_existing() 
{	
			na = newinstall(a,defna,defnsa,0);
      char *newdefna[] = {"hello","opensource","world"};
      int newdefnsa = 3;
			na = newinstall(a,newdefna,newdefnsa,0);
            mu_assert("overwrite an existing name", !strcmp(na->defn[0],"hello") && !strcmp(na->defn[1],"opensource") && !strcmp(na->defn[2],"world"));
            return 0;
}

/*tries to newlookup a created nlist*/
  static char * test_newlookup_existing() 
{			
			na = newinstall(a,defna,defnsa,0);
			na = newlookup(a,0);
            mu_assert("newlookup created nlist", !strcmp(na->defn[0],"world") && !strcmp(na->defn[1],"programmers"));
            return 0;
}

/*tries to newlookup a non existing nlist*/
  static char * test_newlookup_null() 
{
			na = newlookup(b,0);
            mu_assert("newlookup non existing nlist", na == NULL);
            return 0;
}
 
 static char * all_tests() {
    mu_run_test(test_newinstall_create);    
    mu_run_test(test_newinstall_existing);    
    mu_run_test(test_newlookup_existing);    
    mu_run_test(test_newlookup_null);    
     return 0;

 }
 
 int main(int argc, char **argv) {

	char *result = all_tests();
	if (result != 0) {
	 printf("%s\n", result);
	}
	else {
	 // printf("READING TEST PASSED\n");
	}
	// printf("Tests run: %d\n", tests_run);

 return result != 0;
 }
