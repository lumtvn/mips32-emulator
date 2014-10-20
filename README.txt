mips32-emulator
===============

1- in folder mips32-emulator, enter 
-make 

2- then
-make test

3- if all tests passed, 
-make install

After this, if "emul-mips" is entered in command line, the IDE will be initialized. It understands every single command in the requirements, but only processes the following: exit, load, disp, set and assert

If "emul-mips + path to a file" is entered, the output will be the text in the file without the commentary (without any text preceeded by the character '#'). After this, the IDE will start normally, having the same behaivour as described.

commands limitations:

- load accepts only the full path of the script
- there may be some bugs with the environment commands, the tests are not exhaustive yet.