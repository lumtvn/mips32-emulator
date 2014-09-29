#executable files go in bin folder
#.o files go in build folder
# .c and .h files go in scr folder

#make test compiles the tests
#make clear deletes unnecesary files

all: bin/emul-mips

bin/emul-mips: build/interpreter.o
	gcc -pg build/interpreter.o -o bin/emul-mips

build/interpreter.o: src/interpreter.c src/interpreter.h src/headers.h
	gcc -pg -c src/interpreter.c -o build/interpreter.o

test: test/test_parsing test/test_parsing2

test/test_parsing: build/test_parsing.o build/interpreter.o
	gcc build/test_parsing.o build/interpreter.o -o test/test_parsing

test/test_parsing2: build/test_parsing2.o build/interpreter.o
	gcc build/test_parsing2.o build/interpreter.o -o test/test_parsing2

build/test_parsing.o: test/test_parsing.c src/interpreter.h src/headers.h
	gcc -pg -c test/test_parsing.c -o build/test_parsing.o

build/test_parsing2.o: test/test_parsing2.c src/interpreter.h src/headers.h
	gcc -pg -c test/test_parsing2.c -o build/test_parsing2.o