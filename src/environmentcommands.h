struct mipsstr *env_load(struct mipsstr *mips);
struct mipsstr *env_run(struct mipsstr *mips);
struct mipsstr *env_step(struct mipsstr *mips);
struct mipsstr *env_set(struct mipsstr *mips);
struct mipsstr *env_disp(struct mipsstr *mips);
struct mipsstr *env_assert(struct mipsstr *mips);
struct mipsstr *env_disasm(struct mipsstr *mips);
struct mipsstr *env_break(struct mipsstr *mips);
int find_illegal_character(char * s);
