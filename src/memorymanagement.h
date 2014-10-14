struct *mmemory createblock(struct *mmemory mem);

typedef struct mword { char x[4]; } mword;
typedef char mbyte;
typedef struct mhalfword { char x[2]; } mhalfword;

struct mmemory
{
	bool type; /// rom or ram?
	mword simbase; ///base address simulated (in the emulated procesor's memory)
	mbyte *realbase ///real base address (in host RAM)
	int size; /// block size in bytes
	char *tag; /// block's tag (.text, .data, etc)
};