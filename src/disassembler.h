static word const SPECIAL = 0X0;
static word const SPECIAL3 = 0X1F;
static word const REGIMM = 0X1;

typedef int instr_type;
enum{
	R_TYPE, I_TYPE, J_TYPE
};



int load_opcodes(void);
struct ptype *disassemble(struct ptype *mips);
struct ptype *getopcode(struct ptype *mips, word a);
struct ptype *get_normalopcode(struct ptype *mips, word a);
struct ptype *get_specialopcode(struct ptype *mips, word a);
struct ptype *get_special3opcode(struct ptype *mips, word a);
struct ptype *get_regimmopcode(struct ptype *mips, word a);
word get_loc(word opcode);
