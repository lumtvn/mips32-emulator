struct ptype *env_load(struct ptype *mips);
struct ptype *env_run(struct ptype *mips);
struct ptype *env_step(struct ptype *mips);
struct ptype *env_set(struct ptype *mips);
struct ptype *env_disp(struct ptype *mips);
struct ptype *env_assert(struct ptype *mips);
struct ptype *env_disasm(struct ptype *mips);
struct ptype *env_break(struct ptype *mips);
int find_illegal_character(char * s);
