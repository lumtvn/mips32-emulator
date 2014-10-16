
typedef unsigned int mword;
typedef unsigned short int mhw; // half word
typedef unsigned char mbyte;


struct mmemory
{
//for creating purposes
	char *tag; /// block's tag (.text, .data, etc)
	bool type; /// rom or ram?
	int simpoint; ///memory pointer simulated (in the emulated procesor's memory)
	mbyte *realpoint; ///real memory pointer (in host RAM)
	mbyte *realpointbase; ///real memory pointer with fixed direction to the start of the memory segment. This is for making the reading easier
	int blocksize; /// block size in bytes
	
	mword wdata; ///1 word of data to write to or read from memory block
	mhw hwdata; ///1 half word of data to write to or read from memory block
	mbyte bdata; ///1 byte of data to write to or read from memory block
};
struct mmemory *createtagblock(struct mmemory *mem);
struct mmemory *writebyte(struct mmemory *mem);
struct mmemory *writehalfword(struct mmemory *mem);
struct mmemory *writeword(struct mmemory *mem);
struct mmemory *readbyte(struct mmemory *mem);
struct mmemory *readhalfword(struct mmemory *mem);
struct mmemory *readword(struct mmemory *mem);

void displaymemory(struct mmemory *mem);
