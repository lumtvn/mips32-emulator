#include "../src/headers.h"
#include "../src/lookup.h"
#include "minunit.h"

 int tests_run = 0;
 int res;
 struct nlist nna;
 struct nlist *na = &nna;
 char *a = "hello";
 char *b = "foo";

/*tries to install a defn in a non existing name*/
  static char * test_install_create() 
{
			na = install(a, "world",0);
            mu_assert("install non existing name", !strcmp(na->name[0],"hello") && !strcmp(na->defn,"world"));
            return 0;
}

/*tries to overwrite a defn in an existing name*/
  static char * test_install_existing() 
{	
			na = install(a,"world");
			na = install(a,"new world");
            mu_assert("overwrite an existing name", !strcmp(na->defn,"new world"));
            return 0;
}

/*tries to lookup a created nlist*/
  static char * test_lookup_existing() 
{			
			na = install(a,"world");
			na = lookup(a);
            mu_assert("lookup created nlist", !strcmp(na->defn,"world"));
            return 0;
}

/*tries to lookup a non existing nlist*/
  static char * test_lookup_null() 
{
			na = lookup(b);
            mu_assert("lookup non existing nlist", na == NULL);
            return 0;
}
 
 static char * all_tests() {
    mu_run_test(test_install_create);    
    mu_run_test(test_install_existing);    
    mu_run_test(test_lookup_existing);    
    mu_run_test(test_lookup_null);    
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
