#include "../elfapi/include/common/bits.h"
#include "../elfapi/include/common/notify.h"
#include "../elfapi/include/elf/elf.h"
#include "../elfapi/include/elf/syms.h"
#include "../elfapi/include/mem.h"
#include "headers.h"
#include "memorymanagement.h"
#include "elfmanager.h"
#include <errno.h>

#define START_MEM 0x3000



struct ptype *my_init_mem(struct ptype *mips, char *filename)
{
    char* section_names[NB_SECTIONS]= {TEXT_SECTION_STR,RODATA_SECTION_STR,DATA_SECTION_STR,BSS_SECTION_STR};
    unsigned int segment_permissions[NB_SECTIONS]= {R_X,R__,RW_,RW_};
	FILE *fp;
    unsigned int nsegments;
    unsigned int endianness;   //little or big endian
    unsigned int bus_width;    // 32 bits or 64bits
    unsigned int machine_type;
    int i=0,j=0;
    unsigned int next_segment_start = START_MEM;

    mem memory;  // virtual memory, it will contain all of the program's data
    stab symtab= new_stab(0); // table des symboles

    fp = fopen(filename,"r");
	if (fp == NULL){mips->report = 100; printf("%s",strerror(errno));/*no such file*/ return mips;}

	if (!assert_elf_file(fp)) {mips->report = 101;/*is not an elf file*/ return mips;}

	// get architecture
    elf_get_arch_info(fp, &machine_type, &endianness, &bus_width);
    // get simbols
    elf_load_symtab(fp, bus_width, endianness, &symtab);
    // get number of segments
    nsegments = get_nsegments(symtab,section_names,NB_SECTIONS);

    // allouer la memoire virtuelle
    memory=init_mem(nsegments);


        // Ne pas oublier d'allouer les differentes sections
    j=0;
    for (i=0; i<NB_SECTIONS; i++) 
    {
        if (is_in_symbols(section_names[i],symtab)) 
        {
            elf_load_section_in_memory(fp,memory, section_names[i],segment_permissions[i],next_segment_start);

            /*transition to my code*/
            mips = createsegment(mips, section_names[i], memory->seg[j].size._32, segment_permissions[i], next_segment_start);
            /*end transition*/

            next_segment_start+= ((memory->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k suppérieur
            j++;
        }
    }

    // on fait le ménage avant de partir
    del_mem(memory);
    del_stab(symtab);
    fclose(fp);
    puts("");

    mips->report = 0;


    return mips;



}


// Fonction permettant de verifier si une chaine de caracteres
// est bien dans la liste des symboles du fichier ELF
// parametres :
// 		name : le nom de la chaine recherchée
//  symtab : la table des symboles
//
// retourne 1 si present, 0 sinon
int is_in_symbols(char* name, stab symtab) {
    int i;
    for (i=0; i<symtab.size; i++) {
        if (!strcmp(symtab.sym[i].name,name)) return 1;
    }
    return 0;
}

// Cette fonction calcule le nombre de segments à prevoir
// Elle cherche dans les symboles si les sections predefinies
// s'y trouve
// parametres :
//  symtab : la table des symboles
//
// retourne le nombre de sections trouvées

unsigned int get_nsegments(stab symtab,char* section_names[],int nb_sections) {
    unsigned int n=0;
    int i;
    for (i=0; i<nb_sections; i++) {
        if (is_in_symbols(section_names[i],symtab)) n++;
    }
    return n;
}


// fonction permettant d'extraire une section du fichier ELF et de la chargée dans le segment du même nom
// parametres :
//   fp         : le pointeur du fichier ELF
//   memory     : la structure de mémoire virtuelle
//   scn        : le nom de la section à charger
//   permission : l'entier représentant les droits de lecture/ecriture/execution
//   add_start  : l'addresse virtuelle à laquelle la section doit être chargée
//
// retourne 0 en cas de succes, une valeur non nulle sinon
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start) 
{
    byte *ehdr    = __elf_get_ehdr( fp );
    byte *content = NULL;
    uint  textsz  = 0;
    vsize sz;
    vaddr addr;

    byte *useless = elf_extract_section_header_table( ehdr, fp );
    free( useless );

    if ( NULL == ehdr ) {
        WARNING_MSG( "Can't read ELF file" );
        return 1;
    }

    if ( 1 == attach_scn_to_mem(memory, scn, SCN_ATTR( WIDTH_FROM_EHDR( ehdr ), permissions ) ) ) {
        WARNING_MSG( "Unable to create %s section", scn );
        free( ehdr );
        return 1;
    }

    content = elf_extract_scn_by_name( ehdr, fp, scn, &textsz, NULL );
    if ( NULL == content ) {
        WARNING_MSG( "Corrupted ELF file" );
        free( ehdr );
        return 1;
    }

    switch( WIDTH_FROM_EHDR(ehdr) ) {
    case 32 :
        sz._32   = textsz/*+8*/; /* +8: In case adding a final sys_exit is needed */
        addr._32 = add_start;
        break;
    case 64 :
        sz._64   = textsz/*+8*/; /* +8: In case adding a final sys_exit is needed */
        addr._64 = add_start;
        break;
    default :
        WARNING_MSG( "Wrong machine width" );
        return 1;
    }

    if ( 1 == fill_mem_scn(memory, scn, sz, addr, content ) ) {
        free( ehdr );
        free( content );
        WARNING_MSG( "Unable to fill in %s segment", scn );
        return 1;
    }

    free( content );
    free( ehdr );

    return 0;
}