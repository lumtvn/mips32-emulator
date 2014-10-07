mips32-emulator
===============

1- in folder mips32-emulator, enter 
-make 

2- then
-make test

3- if all tests passed, 
-make install

After this, if "emul-mips" is entered in command line, the IDE will be initialized. It understands every single command in the requirements, but does not process any except for "exit".

If "emul-mips + path to a file" is entered, the output will be the text in the file without the commentary (without any text preceeded by the character '#'). After it prints it in the screen, the IDE will start normally, having the same behaivour as described.