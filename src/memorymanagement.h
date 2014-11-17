
struct ptype *creatememory(struct ptype *mem, int size);
struct ptype *destroymemory(struct ptype *mips);
struct ptype *writebyte(struct ptype *mem, mbyte bdata, int simpoint);
struct ptype *writehalfword(struct ptype *mem, mhalfword hwdata, int simpoint);
struct ptype *writeword(struct ptype *mem, mword bdata, int simpoint);
mbyte readbyte(struct ptype *mem, int simpoint);
mhalfword readhalfword(struct ptype *mem, int simpoint);
mword readword(struct ptype *mem, int simpoint);
struct ptype *displaymemory(struct ptype *mem);
struct ptype *createsegment(struct ptype *mips, char *name, int size, int permissions, int start);
