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
struct mipsstr *disasm_instr(struct mipsstr *mips, vaddr32 addr, action ac);
struct mipsstr *getopcode(struct mipsstr *mips, word a);
struct mipsstr *which_operation_number(struct mipsstr *mips);
struct mipsstr *send_operation(struct mipsstr *mips, action ac);
struct mipsstr *manage_normal(struct mipsstr *mips, word instr);
struct mipsstr *manage_special(struct mipsstr *mips, word instr);
struct mipsstr *manage_special3(struct mipsstr *mips, word instr);
struct mipsstr *manage_regimm(struct mipsstr *mips, word instr);
struct mipsstr *run(struct mipsstr *mips);
word get_loc(word opcode);