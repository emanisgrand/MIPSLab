# MIPSLab
Some MIPS assembly language codes. These will work in the MIPS Simulator, MARS.

fibonacci.asm is an implementation of the fibonacci sequence.

SimpleArray.asm is a program that handles simple array operations such as adding a value and storing it to a specific location in the array. 

ShellSort.asm is an implementation of the shell sort algorithm in MIPS.

MIPSDecoder.c - when run in the terminal, pass in a 32-bit binary string that is a valid MIPS instruction code, and the program will decode and print the actual assembly instruction. e.g.

./a.out 00000010001100100100000000100000
add $t0 $s1 $s2
