#executable files go in bin folder, includes test executables
#.o files go in build folder
# .c and .h files go in scr folder

#make test compiles the tests
#make clear deletes unnecesary files


###############################--MAIN FILES COMPILATION--################################
#########################################################################################


all: bin/emul-mips

bin/emul-mips: build/main.o build/environment.o build/environmentcommands.o build/disassembler.o build/memorymanagement.o build/errors.o build/lookup.o build/elfmanager.o ../elfapi/src/bits.o ../elfapi/src/elf.o ../elfapi/src/mem.o ../elfapi/src/section.o ../elfapi/src/syms.o
	gcc -pg build/main.o build/environment.o build/disassembler.o build/environmentcommands.o build/memorymanagement.o build/errors.o build/lookup.o -o bin/emul-mips

build/main.o: src/main.c src/headers.h src/environment.h src/disassembler.h src/memorymanagement.h src/lookup.h
	gcc -pg -c src/main.c -o build/main.o

build/environmentcommands.o: src/environmentcommands.c src/environmentcommands.h src/disassembler.h src/headers.h src/memorymanagement.h src/errors.h src/lookup.h
	gcc -pg -c src/environmentcommands.c -o build/environmentcommands.o

build/environment.o: src/environment.c src/environment.h src/environmentcommands.h src/headers.h src/errors.h
	gcc -pg -c src/environment.c -o build/environment.o

build/disassembler.o: src/disassembler.c src/disassembler.h src/headers.h src/errors.h src/environment.h src/lookup.h
	gcc -pg -c src/disassembler.c -o build/disassembler.o

build/lookup.o: src/lookup.c src/lookup.h src/headers.h
	gcc -pg -c src/lookup.c -o build/lookup.o

build/memorymanagement.o: src/memorymanagement.c src/headers.h src/lookup.h
	gcc -pg -c src/memorymanagement.c -o build/memorymanagement.o

build/errors.o: src/errors.c src/errors.h
	gcc -pg -c src/errors.c -o build/errors.o

build/elfmanager.o: src/elfmanager.c src/elfmanager.h src/memorymanagement.h ../elfapi/include/mem.h ../elfapi/include/elf/syms.h ../elfapi/include/elf/elf.h ../elfapi/include/common/notify.h ../elfapi/include/common/bits.h
	gcc -pg -c src/elfmanager.c -o build/elfmanager.o

../elfapi/src/bits.o: ../elfapi/src/bits.c ../elfapi/include/common/types.h ../elfapi/include/common/bits.h
	gcc -pg -c ../elfapi/src/bits.c -o ../elfapi/src/bits.o

../elfapi/src/elf.o: ../elfapi/src/elf.c ../elfapi/include/common/notify.h ../elfapi/include/common/bits.h ../elfapi/include/elf/elf.h ../elfapi/include/elf/formats.h
	gcc -pg -c ../elfapi/src/elf.c -o ../elfapi/src/elf.o

../elfapi/src/mem.o: ../elfapi/src/mem.c ../elfapi/include/mem.h ../elfapi/include/common/notify.h ../elfapi/include/common/bits.h
	gcc -pg -c ../elfapi/src/mem.c -o ../elfapi/src/mem.o

../elfapi/src/section.o: ../elfapi/src/section.c ../elfapi/include/elf/section.h ../elfapi/include/common/notify.h
	gcc -pg -c ../elfapi/src/section.c -o ../elfapi/src/section.o

../elfapi/src/syms.o: ../elfapi/src/syms.c ../elfapi/include/elf/syms.h ../elfapi/include/common/notify.h
	gcc -pg -c ../elfapi/src/syms.c -o ../elfapi/src/syms.o

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

test: testdisassembler testelfmanager testautoload testenvironment testmemorymanagement testenvironmentcommands testlookup
	@echo ALL TESTS PASSED

###########################--disassembler TESTS--################################
#tests disassembler functions of source file disassembler.c

testdisassembler: bin/test_disassembler
	@echo starting disassembler test
	@./bin/test_disassembler 
	@echo disassembler tests passed

bin/test_disassembler: build/test_disassembler.o build/disassembler.o build/errors.o build/environment.o build/environmentcommands.o build/memorymanagement.o build/lookup.o
	@gcc -pg build/test_disassembler.o build/disassembler.o build/errors.o build/environment.o build/environmentcommands.o build/memorymanagement.o build/lookup.o -o bin/test_disassembler

build/test_disassembler.o: test/test_disassembler.c src/disassembler.h src/headers.h src/environment.h src/environmentcommands.h src/memorymanagement.h src/lookup.h
	@gcc -c test/test_disassembler.c -o build/test_disassembler.o

###########################--environment TESTS--################################
#tests functions of source file environment.c

testenvironment: bin/emul-mips bin/test_environment
	@echo starting environment tests
	@./bin/emul-mips < test/commandfiles/test_environment_commands.txt > test/resultfiles/test_environment_result.txt
	@./bin/test_environment
	@echo environment tests passed

bin/test_environment: build/test_environment.o build/environment.o build/environmentcommands.o build/disassembler.o build/errors.o build/memorymanagement.o build/lookup.o
	@gcc build/test_environment.o build/environment.o build/environmentcommands.o build/disassembler.o build/errors.o build/memorymanagement.o build/lookup.o -o bin/test_environment

build/test_environment.o: test/test_environment.c src/headers.h
	@gcc -pg -c test/test_environment.c -o build/test_environment.o

###########################--AUTOLOAD TESTS--################################
#tests the autoloading function of the environment, passing a file argument when initiating the emulator
testautoload: bin/emul-mips bin/test_autoloader
	@echo starting autoloader tests
	@./bin/emul-mips ./test/testscript.elf < test/commandfiles/test_autoloader_commands.txt > test/resultfiles/test_autoloader_result.txt
	@./bin/test_autoloader
	@echo test autoloader passed

bin/test_autoloader: build/test_autoloader.o
	@gcc build/test_autoloader.o -o bin/test_autoloader

build/test_autoloader.o: test/test_autoloader.c src/headers.h
	@gcc -pg -c test/test_autoloader.c -o build/test_autoloader.o

###########################--LOOKUP TESTS--################################
#tests the lookup functions from file lookup.c

testlookup: bin/test_lookup
	@echo starting lookup tests
	@./bin/test_lookup
	@echo lookup tests passed

bin/test_lookup: build/test_lookup.o build/lookup.o
	@gcc build/test_lookup.o build/lookup.o -o bin/test_lookup

build/test_lookup.o: test/test_lookup.c src/lookup.h src/headers.h
	@gcc -pg -c test/test_lookup.c -o build/test_lookup.o

###########################--ENVIRONMENT COMMANDS TESTS--################################
#tests the functions in charge of executing the environment commands

testenvironmentcommands: bin/emul-mips bin/test_environmentcommands
	@echo starting environmentcommands tests
	@./bin/emul-mips < test/commandfiles/test_load_commands.txt > test/resultfiles/test_load_result.txt 2>&1
	@./bin/emul-mips < test/commandfiles/test_set_reg_commands.txt > test/resultfiles/test_set_reg_result.txt 2>&1
	@./bin/emul-mips < test/commandfiles/test_set_mem_byte_commands.txt > test/resultfiles/test_set_mem_byte_result.txt 2>&1
	@./bin/emul-mips < test/commandfiles/test_set_mem_word_commands.txt > test/resultfiles/test_set_mem_word_result.txt 2>&1
	@./bin/emul-mips < test/commandfiles/test_disp_reg_commands.txt > test/resultfiles/test_disp_reg_result.txt 2>&1
	@./bin/emul-mips < test/commandfiles/test_assert_commands.txt > test/resultfiles/test_assert_result.txt 2>&1
	@./bin/test_environmentcommands
	@echo environmentcommands tests passed

bin/test_environmentcommands: build/test_environmentcommands.o build/environmentcommands.o build/disassembler.o build/memorymanagement.o build/errors.o build/lookup.o
	@gcc build/test_environmentcommands.o build/environmentcommands.o build/disassembler.o build/memorymanagement.o build/errors.o build/lookup.o -o bin/test_environmentcommands

build/test_environmentcommands.o: test/test_environmentcommands.c src/environmentcommands.h src/headers.h src/disassembler.h src/errors.h src/memorymanagement.h
	@gcc -pg -c test/test_environmentcommands.c -o build/test_environmentcommands.o

###########################--MEMORY MANAGEMENT TESTS--################################
#tests the functions in charge of managing the memory of the simulated processor

testmemorymanagement: bin/test_memorymanagement
	@echo starting memorymanagement tests
	@./bin/test_memorymanagement
	@echo memorymanagement tests passed

bin/test_memorymanagement: build/test_memorymanagement.o build/memorymanagement.o build/lookup.o
	@gcc build/test_memorymanagement.o build/memorymanagement.o build/lookup.o -o bin/test_memorymanagement

build/test_memorymanagement.o: test/test_memorymanagement.c src/memorymanagement.h src/headers.h src/lookup.h
	@gcc -pg -c test/test_memorymanagement.c -o build/test_memorymanagement.o


testelfmanager: bin/test_elfmanager
	@echo starting elfmanager tests
	@./bin/test_elfmanager
	@echo elfmanager tests passed

bin/test_elfmanager: build/test_elfmanager.o build/elfmanager.o build/memorymanagement.o build/lookup.o ../elfapi/src/bits.o ../elfapi/src/elf.o ../elfapi/src/mem.o ../elfapi/src/section.o ../elfapi/src/syms.o
	@gcc build/test_elfmanager.o build/elfmanager.o build/memorymanagement.o build/lookup.o ../elfapi/src/bits.o ../elfapi/src/elf.o ../elfapi/src/mem.o ../elfapi/src/section.o ../elfapi/src/syms.o -o bin/test_elfmanager

build/test_elfmanager.o: test/test_elfmanager.c src/elfmanager.h src/headers.h src/lookup.h src/memorymanagement.h ../elfapi/include/mem.h ../elfapi/include/elf/syms.h ../elfapi/include/elf/elf.h ../elfapi/include/common/notify.h ../elfapi/include/common/bits.h
	@gcc -pg -c test/test_elfmanager.c -o build/test_elfmanager.o


##########clean unnecesary files

clear: 
	find . -name *.o -delete
	rm -f *~