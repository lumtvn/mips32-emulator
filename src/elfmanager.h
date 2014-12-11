#define TEXT_SECTION_STR ".text"
#define RODATA_SECTION_STR ".rodata"
#define DATA_SECTION_STR ".data"
#define BSS_SECTION_STR ".bss"
#define NB_SECTIONS 4

static char* section_names[NB_SECTIONS]= {TEXT_SECTION_STR,RODATA_SECTION_STR,DATA_SECTION_STR,BSS_SECTION_STR};
static unsigned int segment_permissions[NB_SECTIONS]= {R_X,R__,RW_,RW_};

struct elfstr *start_and_load(struct elfstr *elfdata, char *filename, uint start_mem);
int is_in_symbols(char* name, stab symtab);
unsigned int get_nsegments(stab symtab,char* section_names[],int nb_sections);
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start);
void destroy_mem(struct elfstr *elfdata);
bool is_in_segment(segment *seg, vaddr32 v, uint size);
segment *get_seg_by_name( mem m, char *name);
segment *which_seg( mem m, vaddr32 v, uint size);
struct elfstr *start_mem(struct elfstr *elfdata);
struct mipsstr *elfwritebyte(struct mipsstr *mips, mem m, byte bdata, vaddr32 addr);
struct mipsstr *elfwriteword(struct mipsstr *mips, mem m, word wdata, vaddr32 addr);
struct mipsstr *elfreadbyte(struct mipsstr *mips, mem m, vaddr32 addr);
struct mipsstr *elfreadword(struct mipsstr *mips, mem m, vaddr32 addr);
uint32_t get_seg_size(mem m, char *name);
vaddr32 get_seg_start(mem m, char *name);
void print_segment_raw_content(segment* seg);