/**
 * @file elfmanager.c
 * @author Luciano Mantovani
 * @date November 2014
 * @brief file containing functions to work with an elf file. this file uses functions from the directory elfapi
 * 
 * @details apart from the functions found in file mipself_test.c, i added a few functions that
 * allow me to interact with the memory block created by the elf api
 *
 * 
 *
 **/

#include "headers.h"
#include "elfmanager.h"

#define START_MEM 0x3000

/**
 * @brief function to get a segment from a string and a memory
 * @details this function searches all the segments in a created memory for one that has an name equal to the name parameter
 * 
 * @param m the memory. It has to be already initialized
 * @param name the name of the segment
 * 
 * @return returns the segment if found. NULL if no segment asociated to that name
 */
segment *get_seg_by_name( mem m, char *name)
{
    int i;
    for(i = 0; i< m->nseg; i++)
    {
        if(!strcmp(m->seg[i].name, name))
            return &m->seg[i];
    }
    //no segment found with that name!
    return NULL;
}

/**
 * @brief function to know if an address range is inside a specific segment
 * 
 * @param seg the segment to evaluate
 * @param v the start address
 * @param size the range
 * @return true if belongs to segment. false if not
 */
bool is_in_segment(segment *seg, vaddr32 v, uint size)
{ 
    if(v < seg->start._32)
        return false;
    if(v + size - 1 > seg->start._32 + seg->size._32 - 1)
        return false;

    //if in-bounds, it belongs to this segment  
    return true;
}
/**
 * @brief given an address v and a range size, this function returns the segment asociated to that range
 * 
 * @param m the memory where the segment exists
 * @param v starting address
 * @param size range
 * @return the segment asociated to the range. NULL if no segment found
 */
 segment *which_seg( mem m, vaddr32 v, uint size)
{
    int i;
    for(i = 0; i<m->nseg; i++)
    {
        if(is_in_segment(&m->seg[i], v, size))
            return &m->seg[i];
    }
    //address doesn't belong to any segment

    return NULL;
}

/**
 * @brief function very similar to main() in mipself_test.c
 * @details it's used to load data into host memory, given an elf file
 * 
 * @param elfstr the structure holding data concerning the symbol table, the memory, and the file pointer
 * @param filename the name of the elf binary file
 * @param start_mem the starting address of the memory
 * @return the structure with the memory, the symtable, and the file pointer. for further usage by program
 */
struct elfstr *start_and_load(struct elfstr *elfdata, char *filename, uint start_mem)
{
    unsigned int nsegments;
    int i=0,j=0;
    unsigned int type_machine;
    unsigned int endianness;   //little ou big endian
    unsigned int bus_width;    // 32 bits ou 64bits
    unsigned int next_segment_start = start_mem; // compteur pour designer le début de la prochaine section

    elfdata->symtab = new_stab(0);

    if ((elfdata->pf_elf = fopen(filename,"r")) == NULL) {
        elfdata->report = 100;
        return elfdata;
    }

    if (!assert_elf_file(elfdata->pf_elf))
    {
        elfdata->report = 101;
        return elfdata;
    }


    // recuperation des info de l'architecture
    elf_get_arch_info(elfdata->pf_elf, &type_machine, &endianness, &bus_width);
    // et des symboles
    elf_load_symtab(elfdata->pf_elf, bus_width, endianness, &(elfdata->symtab));


    nsegments = get_nsegments(elfdata->symtab,section_names,NB_SECTIONS);

    // allouer la memoire virtuelle
    elfdata->memory=init_mem(nsegments);

    j=0;
    for (i=0; i<NB_SECTIONS; i++) {
        if (is_in_symbols(section_names[i],elfdata->symtab)) {
            elf_load_section_in_memory(elfdata->pf_elf,elfdata->memory, section_names[i],segment_permissions[i],next_segment_start);
            next_segment_start+= ((elfdata->memory->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k suppérieur
            j++;
        }
    }

    elfdata->report = 0;
    return elfdata;
}

/**
 * @brief writes a byte in a memory section, as long as allowed by it's permissions
 * 
 * @param mips->bdata it changes this field of mips
 * @param m reference to memory being used
 * @param bdata byte to write
 * @param addr address to write byte
 */
struct mipsstr *elfwritebyte(struct mipsstr *mips, mem m, byte bdata, vaddr32 addr)
{
    segment *seg;
    seg = which_seg(m,addr,1);
    if(seg == NULL){mips->report = 501;  /*no segment asociated to address*/ return mips;}
    if(seg->content == NULL){mips->report = 502; /*can't write to null content*/ return mips;}
    if(SCN_RIGHTS(seg->attr) != RW_){mips->report = 503; /*no writing permissions for this segment*/ return mips;}

    // printf("0x%x\n", *(seg->content + addr - seg->start._32));
    *(seg->content + addr - seg->start._32) = bdata;
    mips->report = 0;

    return mips;
}
/**
 * @brief reads a byte in a memory section
 * 
 * @param mips->bdata it changes this field of mips
 * @param m reference to memory being used
 * @param addr address to read byte
 */
struct mipsstr *elfreadbyte(struct mipsstr *mips, mem m, vaddr32 addr)
{
    segment *seg;
    seg = which_seg(m,addr,1);
    if(seg == NULL){mips->report = 501;  /*no segment asociated to address*/ return mips;}
    if(seg->content == NULL){mips->report = 502; /*can't read to null content*/ return mips;}

    mips->bdata = *(seg->content + addr - seg->start._32);
    mips->report = 0;
    return mips;
}
/**
 * @brief writes a word in a memory section, as long as allowed by it's permissions
 * 
 * @param mips->wdata it changes this field of mips
 * @param m reference to memory being used
 * @param bdata word to write
 * @param addr address to write word
 */
struct mipsstr *elfwriteword(struct mipsstr *mips, mem m, word wdata, vaddr32 addr)
{
    segment *seg;
    seg = which_seg(m,addr,4);
    if(seg == NULL){mips->report = 501;  /*no segment or address out of bounds*/ return mips;}
    if(seg->content == NULL){mips->report = 502; /*can't write to null content*/ return mips;}
    if(SCN_RIGHTS(seg->attr) != RW_){mips->report = 503; /*no writing permissions for this segment*/ return mips;}


    // printf("0x%x\n", *(seg->content + addr - seg->start._32));
    *(seg->content + addr - seg->start._32) = (wdata >> 24) & 0xFF;
    *(seg->content + addr - seg->start._32 + 1) = (wdata >> 16) & 0xFF;
    *(seg->content + addr - seg->start._32 + 2) = (wdata >> 8) & 0xFF;
    *(seg->content + addr - seg->start._32 + 3) = wdata;

    mips->report = 0;
    return mips;
}
/**
 * @brief reads a word in a memory section
 * 
 * @param mips->wdata it changes this field of mips
 * @param m reference to memory being used
 * @param addr address to read word
 */
struct mipsstr *elfreadword(struct mipsstr *mips, mem m, vaddr32 addr)
{
    segment *seg;
    seg = which_seg(m,addr,4);
    if(seg == NULL){mips->report = 501;  /*no segment asociated to address*/ return mips;}

    if(seg->content == NULL){mips->report = 502; /*can't read null content*/ return mips;}

    mips->wdata = (*(seg->content + addr - seg->start._32) << 24) | (*(seg->content + addr - seg->start._32+1) << 16) | (*(seg->content + addr - seg->start._32+2) << 8) | *(seg->content + addr - seg->start._32+3);
    mips->report = 0;


    return mips;
}

/**
 * @brief get size of a segment given a name
 * 
 * @param m the memory where the segment exists
 * @param name name of the segment
 * 
 * @return the segment size if it exists, 0 if it doesn't
 */
uint32_t get_seg_size(mem m, char *name)
{   
    segment *seg;
    seg = get_seg_by_name(m, name);
    if(seg == NULL)
        return 0;

    return seg->size._32;
}
/**
 * @brief gets the start address of a segment
 * 
 * @param m the memory where the segment exists
 * @param name name of the segment
 * 
 * @return the start address of the segment
 */
vaddr32 get_seg_start(mem m, char *name)
{   
    segment *seg;
    seg = get_seg_by_name(m, name);
    if(seg == NULL)
        return 0;

    return seg->start._32;
}

/**
 * @brief resets bdata and wdata
 * 
 * @param mips->bdata is changed in this function
 * @param mips->wdata is changed in this function
 */
struct mipsstr *cleandata(struct mipsstr *mips)
{
    mips->bdata = 0;
    mips->wdata = 0;

    return mips;
}

/**
 * @brief function to clean the memory created. used at end of program
 */
void destroy_mem(struct elfstr *elfdata)
{
    fclose(elfdata->pf_elf);
    del_mem(elfdata->memory);
    del_stab(elfdata->symtab);
    // puts("");
}



///////////
////////// the next functions are identical to those in file mipself_test.c


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

// fonction affichant les octets d'un segment sur la sortie standard
// parametres :
//   seg        : le segment de la mémoire virtuelle à afficher

void print_segment_raw_content(segment* seg) {
    int k;
    printf("\nraw content of segment %s:\n", seg->name);
    int word =0;
    if (seg!=NULL && seg->size._32>0) {
        for(k=0; k<seg->size._32; k+=4) {
            if(k%16==0) printf("\n  0x%08x ",k);
            word = *((unsigned int *) (seg->content+k));
            FLIP_ENDIANNESS(word);
            printf("0x%08x ",   word);
        }
    }
}