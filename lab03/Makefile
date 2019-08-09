all: bit_ops lfsr factorial list_map
.PHONY: all clean

CC=gcc
LD=gcc
CFLAGS=-ggdb -Wall -std=c99
LDFLAGS=

lfsr: lfsr.c
	$(CC) $(CFLAGS) -o lfsr lfsr.c

bit_ops: bit_ops.c
	$(CC) $(CFLAGS) -o bit_ops bit_ops.c

factorial: factorial.s
	@echo "Checking Factorial..."
	@echo "6 720 5040 40320" > factorial_expected.txt
	@java -jar ../venus-jvm-latest.jar factorial.s > factorial_actual.txt
	@diff -w factorial_expected.txt factorial_actual.txt
	@echo "Success!"

list_map: list_map.s
	@echo "Checking list_map..."
	@echo "9 8 7 6 5 4 3 2 1 0\n81 64 49 36 25 16 9 4 1 0" > list_map_expected.txt
	@java -jar ../venus-jvm-latest.jar list_map.s > list_map_actual.txt
	@diff -w list_map_expected.txt list_map_actual.txt
	@echo "Success!"

clean:
	@rm -f factorial_expected.txt factorial_actual.txt
	@rm -f list_map_expected.txt list_map_actual.txt
	@rm lfsr bit_ops
