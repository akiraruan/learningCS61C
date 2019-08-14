CC=gcc
C_FLAGS=--std=c99

simd: simd.c common.c
	$(CC) $(C_FLAGS) -O0 simd.c common.c -o simd

opt: opt0_simd opt1_simd opt2_simd opt3_simd

opt0_simd: simd.c common.c
	$(CC) $(C_FLAGS) -O0 simd.c common.c -o opt0_simd

opt1_simd: simd.c common.c
	$(CC) $(C_FLAGS) -O1 simd.c common.c -o opt1_simd

opt2_simd: simd.c common.c
	$(CC) $(C_FLAGS) -O2 simd.c common.c -o opt2_simd

opt3_simd: simd.c common.c
	$(CC) $(C_FLAGS) -O3 simd.c common.c -o opt3_simd

clean:
	@rm -f simd opt0_simd opt1_simd opt2_simd opt3_simd

