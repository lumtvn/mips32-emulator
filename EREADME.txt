this is the file containing the error and warning codes for all functions, defined in src/errors.c

 100: from file reader.c
	+ 00: from function readscript()
	+ 10: from function removecommentary()

 200: from file assembler.c
	+ 00: from function compile()
	+ 10: from function parseline()

 300: from file environment.c
	+ 00: from function runenv()
	+ 10: from function restart()
	+ 20: from function parseentry()
	+ 30: from function analize()
	+ 40: from function strip()

 400: from file environmentcommands.c
	+ 00: from function env_load
	+ 10: from function env_set
	+ 20: from function env_disp
	
 500: from file memorymanagement.c
	+ 00: from function createblock()
	+ 10: from function writebyte()
	+ 20: from function writehalfword()
	+ 30: from function writeword()
	+ 40: from function readbyte()
	+ 50: from function readhalfword()
	+ 60: from function readword()
	+ 70: from function displaymemory()

	
the list is incomplete