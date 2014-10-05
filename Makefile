#executable files go in bin folder
#executable test files go in test folder
#.o files go in build folder
# .c and .h files go in scr folder

#make test compiles the tests
#make clear deletes unnecesary files


###############################--MAIN FILES COMPILATION--################################
#########################################################################################


all: bin/emul-mips

bin/emul-mips: build/main.o build/reader.o build/enviroment.o build/assembler.o 
	gcc -pg build/main.o build/reader.o build/enviroment.o build/assembler.o -o bin/emul-mips

build/reader.o: src/reader.c src/reader.h src/headers.h
	gcc -pg -c src/reader.c -o build/reader.o

build/enviroment.o: src/enviroment.c src/enviroment.h src/headers.h
	gcc -pg -c src/enviroment.c -o build/enviroment.o

build/assembler.o: src/assembler.c src/assembler.h src/reader.h src/headers.h 
	gcc -pg -c src/assembler.c -o build/assembler.o

build/main.o: src/main.c src/headers.h
	gcc -pg -c src/main.c -o build/main.o

###############################--INSTALL--################################
##########################################################################

install: bin/emul-mips
	chmod 755 bin/emul-mips
	sudo cp bin/emul-mips /usr/local/bin


###############################--TESTS--################################
########################################################################


###########################--ALL TESTS--################################

#enviroment testing is not included in general testing

test: testparser testreader

###########################--PARSING TESTS--################################
#tests parsing functions of source file reader.c

testparser: test/test_parsing test/test_parsing2 test/test_parsing3
	./test/test_parsing 
	./test/test_parsing2
	./test/test_parsing3

test/test_parsing: build/test_parsing.o build/assembler.o
	gcc -pg build/test_parsing.o build/assembler.o -o test/test_parsing

test/test_parsing2: build/test_parsing2.o build/assembler.o
	gcc -pg build/test_parsing2.o build/assembler.o -o test/test_parsing2

test/test_parsing3: build/test_parsing3.o build/assembler.o
	gcc -pg build/test_parsing3.o build/assembler.o -o test/test_parsing3

build/test_parsing.o: test/test_parsing.c src/assembler.h src/headers.h
	gcc -pg -c test/test_parsing.c -o build/test_parsing.o

build/test_parsing2.o: test/test_parsing2.c src/assembler.h src/headers.h
	gcc -pg -c test/test_parsing2.c -o build/test_parsing2.o

build/test_parsing3.o: test/test_parsing3.c src/assembler.h src/headers.h
	gcc -pg -c test/test_parsing3.c -o build/test_parsing3.o

###########################--READER TESTS--################################
#tests reading functions of source file reader.c

testreader: test/test_reader
	./test/test_reader

test/test_reader: build/test_reader.o build/reader.o
	gcc build/test_reader.o build/reader.o -o test/test_reader

build/test_reader.o: test/test_reader.c src/reader.h src/headers.h
	gcc -pg -c test/test_reader.c -o build/test_reader.o

###########################--ENVIROMENT TESTS--################################
#tests functions of source file enviroment.c

testenviroment: test/test_enviroment
	./test/test_enviroment

test/test_enviroment: build/test_enviroment.o build/enviroment.o
	gcc build/test_enviroment.o build/enviroment.o -o test/test_enviroment

build/test_enviroment.o: test/test_enviroment.c src/reader.h src/headers.h
	gcc -pg -c test/test_enviroment.c -o build/test_enviroment.o

###########################--AUTOLOAD TESTS--################################
#tests the autoloading function of the enviroment, passing a file argument when initiating the emulator
testautoload: bin/emul-mips
	./bin/emul-mips ./test/testscript.elf

clear: 
	find . -name *.o -delete
	rm -f *~