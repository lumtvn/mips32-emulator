static word const SPECIAL = 0X0;
static word const SPECIAL3 = 0X1F;
static word const REGIMM = 0X1;

typedef int instr_type;
enum{
	R_TYPE, I_TYPE, J_TYPE
};

typedef int action;
enum{
	D_PRINT, D_EXEC
};



int load_opcodes(void);
struct ptype *disasm_instr(struct ptype *mips, vaddr32 addr, action ac);
struct ptype *getopcode(struct ptype *mips, word a);
struct ptype *which_operation_number(struct ptype *mips);
struct ptype *send_operation(struct ptype *mips, action ac);
struct ptype *manage_normal(struct ptype *mips, word instr);
struct ptype *manage_special(struct ptype *mips, word instr);
struct ptype *manage_special3(struct ptype *mips, word instr);
struct ptype *manage_regimm(struct ptype *mips, word instr);
struct ptype *run(struct ptype *mips);
word get_loc(word opcode);