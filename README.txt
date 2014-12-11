mips32-emulator
===============

1- in folder mips32-emulator, enter 
-make 

2- then
-make test

3- if all tests passed, 
-make install

After this, if "emul-mips" is entered in command line, the IDE will be initialized. It understands every single command in the requirements, with the exception of debug and resume, that were not implemented

If "emul-mips + path to a file + start address" is entered, the program will autoload the file entered as always as it is in elf format, at the direction of the memory specified by start address .After this, the IDE will start normally, having the same behaivour as described.

limitations:

- load accepts only the full path of the script
- This version does not yet implement SYSCALL
- writing permits are set for all registers except for zero


ADDING READLINE:

for better handling of the environment commands, i added readline functionalities to search in command history and enable entering old commands using only the arrows up and down keys. For this to work properly it's necessary that the required libraries are installed. 

	yum install readline-devel         (RPM-based systems)
	apt-get install libreadline-dev   (Debian-based systems)
