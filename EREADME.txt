this is the file containing the error and warning codes for all functions, defined in src/errors.c

 100: from file reader.c
	+ 00: from function readscript()
	+ 10: from function removecommentary()

 300: from file environment.c
	+ 00: from function runenv()
	+ 10: from function restart()
	+ 20: from function parseentry()
	+ 30: from function analize()

 400: from file environmentcommands.c
	+ 00: from function env_load
	+ 10: from function env_set
	+ 20: from function env_disp
	+ 30: from function env_assert

 500: from file elfmanager.c

 600: from file dissassembler.c
 	+ 00: from function disasm_instr

 1000: compilation errors (file operations.c)


	
the list is yet to be completed and some error groups may not be implemented. Some functions may call errors from other functions. This happens when the error is triggered by the same reason.