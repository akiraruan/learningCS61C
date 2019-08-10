all: discrete_fn megalistmanips
.PHONY: all clean

discrete_fn: discrete_fn.s
	@echo "Checking discrete_fn..."
	@java -jar ../venus-jvm-latest.jar discrete_fn.s > discrete_fn_actual.txt
	@diff -w discrete_fn_expected.txt discrete_fn_actual.txt
	@echo "Success!"

megalistmanips: megalistmanips.s
	@echo "Checking megalistmanips..."
	@java -jar ../venus-jvm-latest.jar megalistmanips.s > megalistmanips_actual.txt
	@diff -w megalistmanips_expected.txt megalistmanips_actual.txt
	@echo "Success!"

clean:
	@rm -f discrete_fn_actual.txt
	@rm -f megalistmanips_actual.txt