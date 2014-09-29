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

test: test/test_interpreter

test/test_interpreter: build/test_interpreter.o build/interpreter.o
	gcc build/test_interpreter.o build/interpreter.o -o test/test_interpreter

build/test_interpreter.o: test/test_interpreter.c src/interpreter.h src/headers.h
	gcc -pg -c test/test_interpreter.c -o build/test_interpreter.o