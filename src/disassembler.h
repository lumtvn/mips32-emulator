int load_opcodes(void);
struct ptype *getopcode(struct ptype *mips, word a);
struct ptype *get_normalopcode(struct ptype *mips, word a);
struct ptype *get_specialopcode(struct ptype *mips, word a);
struct ptype *get_special3opcode(struct ptype *mips, word a);
struct ptype *get_regimmopcode(struct ptype *mips, word a);
