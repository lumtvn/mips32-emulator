#executable files go in bin folder, includes test executables
#.o files go in build folder
# .c and .h files go in scr folder

#make test compiles the tests
#make clear deletes unnecesary files


###############################--MAIN FILES COMPILATION--################################
#########################################################################################


all: bin/emul-mips

bin/emul-mips: build/main.o build/reader.o build/environment.o build/environmentcommands.o build/assembler.o 
	gcc -pg build/main.o build/reader.o build/environment.o build/assembler.o build/environmentcommands.o -o bin/emul-mips

build/main.o: src/main.c src/headers.h src/environment.h src/assembler.h
	gcc -pg -c src/main.c -o build/main.o

build/reader.o: src/reader.c src/reader.h src/headers.h
	gcc -pg -c src/reader.c -o build/reader.o

build/environmentcommands.o: src/environmentcommands.c src/environmentcommands.h src/assembler.h src/headers.h src/errors.h
	gcc -pg -c src/environmentcommands.c -o build/environmentcommands.o

build/environment.o: src/environment.c src/environment.h src/environmentcommands.h src/headers.h src/errors.h
	gcc -pg -c src/environment.c -o build/environment.o

build/assembler.o: src/assembler.c src/assembler.h src/reader.h src/headers.h src/errors.h
	gcc -pg -c src/assembler.c -o build/assembler.o

build/newlookup.o: src/newlookup.c src/newlookup.h src/headers.h
	gcc -pg -c src/newlookup.c -o build/newlookup.o

build/memorymanagement.o: src/memorymanagement.c src/headers.h
	gcc -pg -c src/memorymanagement.c -o build/memorymanagement.o


###############################--INSTALL--################################
##########################################################################

install: bin/emul-mips
	chmod 755 bin/emul-mips
	sudo cp bin/emul-mips /usr/local/bin
	@echo done!


###############################--TESTS--################################
########################################################################


###########################--ALL TESTS--################################

#environment testing is not included in general testing

test: testparser testreader testautoload testenvironment
	@echo ALL TESTS PASSED

###########################--PARSING TESTS--################################
#tests parsing functions of source file reader.c

testparser: bin/test_parsing bin/test_parsing2 bin/test_parsing3
	@./bin/test_parsing 
	@./bin/test_parsing2
	@./bin/test_parsing3

bin/test_parsing: build/test_parsing.o build/assembler.o build/reader.o
	@gcc -pg build/test_parsing.o build/assembler.o build/reader.o -o bin/test_parsing

bin/test_parsing2: build/test_parsing2.o build/assembler.o build/reader.o
	@gcc -pg build/test_parsing2.o build/assembler.o build/reader.o -o bin/test_parsing2

bin/test_parsing3: build/test_parsing3.o build/assembler.o build/reader.o
	@gcc -pg build/test_parsing3.o build/assembler.o build/reader.o -o bin/test_parsing3

build/test_parsing.o: test/test_parsing.c src/assembler.h src/headers.h
	@gcc -c test/test_parsing.c -o build/test_parsing.o

build/test_parsing2.o: test/test_parsing2.c src/assembler.h src/headers.h
	@gcc -c test/test_parsing2.c -o build/test_parsing2.o

build/test_parsing3.o: test/test_parsing3.c src/assembler.h src/headers.h
	@gcc -c test/test_parsing3.c -o build/test_parsing3.o

###########################--READER TESTS--################################
#tests reading functions of source file reader.c

testreader: bin/test_reader
	@./bin/test_reader

bin/test_reader: build/test_reader.o build/reader.o
	@gcc build/test_reader.o build/reader.o -o bin/test_reader

build/test_reader.o: test/test_reader.c src/reader.h src/headers.h
	@gcc -pg -c test/test_reader.c -o build/test_reader.o

###########################--environment TESTS--################################
#tests functions of source file environment.c

testenvironment: bin/emul-mips bin/test_environment
	@./bin/emul-mips < test/commandfiles/test_environment_commands.txt > test/resultfiles/test_environment_result.txt
	@./bin/test_environment

bin/test_environment: build/test_environment.o build/environment.o build/environmentcommands.o build/assembler.o build/reader.o
	@gcc build/test_environment.o build/environment.o build/environmentcommands.o build/assembler.o build/reader.o -o bin/test_environment

build/test_environment.o: test/test_environment.c src/reader.h src/headers.h
	@gcc -pg -c test/test_environment.c -o build/test_environment.o

###########################--AUTOLOAD TESTS--################################
#tests the autoloading function of the environment, passing a file argument when initiating the emulator
testautoload: bin/emul-mips bin/test_autoloader
	@./bin/emul-mips ./test/testscript.elf < test/commandfiles/test_autoloader_commands.txt > test/resultfiles/test_autoloader_result.txt
	@./bin/test_autoloader

bin/test_autoloader: build/test_autoloader.o
	@gcc build/test_autoloader.o -o bin/test_autoloader

build/test_autoloader.o: test/test_autoloader.c src/headers.h
	@gcc -pg -c test/test_autoloader.c -o build/test_autoloader.o

###########################--newLOOKUP TESTS--################################
#tests the newlookup functions from file newlookup.c

testnewlookup: bin/test_newlookup
	@./bin/test_newlookup

bin/test_newlookup: build/test_newlookup.o build/newlookup.o
	@gcc build/test_newlookup.o build/newlookup.o -o bin/test_newlookup

build/test_newlookup.o: test/test_newlookup.c src/newlookup.h src/headers.h
	@gcc -pg -c test/test_newlookup.c -o build/test_newlookup.o

###########################--ENVIRONMENT COMMANDS TESTS--################################
#tests the functions in charge of executing the environment commands

testenvironmentcommands: bin/emul-mips bin/test_environmentcommands
	@./bin/emul-mips < test/commandfiles/test_load_commands.txt
	@./bin/test_environmentcommands

bin/test_environmentcommands: build/test_environmentcommands.o build/environmentcommands.o build/assembler.o build/reader.o
	@gcc build/test_environmentcommands.o build/environmentcommands.o build/assembler.o build/reader.o -o bin/test_environmentcommands

build/test_environmentcommands.o: test/test_environmentcommands.c src/environmentcommands.h src/headers.h src/assembler.h src/reader.h
	@gcc -pg -c test/test_environmentcommands.c -o build/test_environmentcommands.o

###########################--MEMORY MANAGEMENT TESTS--################################
#tests the functions in charge of managing the memory of the simulated processor

testmemorymanagement: bin/test_memorymanagement
	./bin/test_memorymanagement

bin/test_memorymanagement: build/test_memorymanagement.o build/memorymanagement.o
	@gcc build/test_memorymanagement.o build/memorymanagement.o -o bin/test_memorymanagement

build/test_memorymanagement.o: test/test_memorymanagement.c src/memorymanagement.h src/headers.h
	@gcc -pg -c test/test_memorymanagement.c -o build/test_memorymanagement.o


##########clean unnecesary files

clear: 
	find . -name *.o -delete
	rm -f *~