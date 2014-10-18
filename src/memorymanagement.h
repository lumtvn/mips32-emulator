
struct ptype *createblock(struct ptype *mem, int size);
struct ptype *writebyte(struct ptype *mem, mbyte bdata, int simpoint);
struct ptype *writehalfword(struct ptype *mem, mhalfword hwdata, int simpoint);
struct ptype *writeword(struct ptype *mem, mword bdata, int simpoint);
mbyte readbyte(struct ptype *mem, int simpoint);
mhalfword readhalfword(struct ptype *mem, int simpoint);
mword readword(struct ptype *mem, int simpoint);
void displaymemory(struct ptype *mem);
