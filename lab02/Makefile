UNAME_S := $(shell uname -s)
CC=gcc
LD=gcc
CFLAGS=-ggdb -Wall -std=c99
LDFLAGS=

ifeq ($(UNAME_S), Darwin)
    MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes --dsymutil=yes --suppressions=osx_vector.supp
endif

ifeq ($(UNAME_S), Linux)
    MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes
endif

VECTOR_OBJS=vector.o vector-test.o
VECTOR_PROG=vector-test

BINARIES=$(VECTOR_PROG) ll_cycle

A_PROG=program_a
B_PROG=program_b
C_PROG=program_c
D_PROG=program_d

.PHONY: all
all: $(BINARIES) lab2_ex4_assembly

$(VECTOR_PROG): $(VECTOR_OBJS)
	$(LD) -o $(VECTOR_PROG) $(VECTOR_OBJS) $(LDFLAGS)

ll_cycle: ll_cycle.c
	$(CC) $(CFLAGS) -o ll_cycle ll_cycle.c

.c.o:
	$(CC) -c -pedantic $(CFLAGS) $<

vector-memcheck: $(VECTOR_PROG)
	$(MEMCHECK) ./$(VECTOR_PROG)

.PHONY: clean
clean: 
	@rm -rf core *.o *~ "#"*"#" Makefile.bak $(BINARIES) *.dSYM
	@rm -f lab2_ex4_assembly_expected.txt lab2_ex4_assembly_actual.txt
	@rm -f program_a program_b program_c program_d
        
vector.c: vector.h
vector-test.c: vector.h

$(A_PROG): program_a.o
	$(LD) -o $(A_PROG) program_a.o $(LDFLAGS)

$(B_PROG): program_b.o
	$(LD) -o $(B_PROG) program_b.o $(LDFLAGS)

$(C_PROG): program_c.o
	$(LD) -o $(C_PROG) program_c.o $(LDFLAGS)

$(D_PROG): program_d.o
	$(LD) -o $(D_PROG) program_d.o $(LDFLAGS)

a-memcheck: $(A_PROG)
	$(MEMCHECK) ./$(A_PROG)

b-memcheck: $(B_PROG)
	$(MEMCHECK) ./$(B_PROG)

c-memcheck: $(C_PROG)
	$(MEMCHECK) ./$(C_PROG)

d-memcheck: $(D_PROG)
	$(MEMCHECK) ./$(D_PROG)

lab2_ex4_assembly: lab2_ex4_assembly.s
	@echo "Checking Exercise 2..."
	@echo "3 1 4 1 5 9\n6 1 8 1 10 1" > lab2_ex4_assembly_expected.txt
	@java -jar ../venus-jvm-latest.jar lab2_ex4_assembly.s > lab2_ex4_assembly_actual.txt
	@diff -w lab2_ex4_assembly_expected.txt lab2_ex4_assembly_actual.txt
	@echo "Success!"

