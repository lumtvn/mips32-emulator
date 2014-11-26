#define TEXT_SECTION_STR ".text"
#define RODATA_SECTION_STR ".rodata"
#define DATA_SECTION_STR ".data"
#define BSS_SECTION_STR ".bss"
#define NB_SECTIONS 4

struct elfstr *start_and_load(struct elfstr *elfdata, char *filename);
int is_in_symbols(char* name, stab symtab);
unsigned int get_nsegments(stab symtab,char* section_names[],int nb_sections);
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start);
void destroy_mem(struct elfstr *elfdata);
bool is_in_segment( mem m,  segment *seg, vaddr32 v);
segment *get_seg_by_name( mem m, char *name);
segment *which_seg( mem m, vaddr32 v);
struct elfstr *start_mem(struct elfstr *elfdata);
