#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH 32
#define false 0
#define true 1

char *regs[] = {
	"$zero",
	"$at",
	"$v0","$v1",
	"$a0","$a1","$a2","$a3",
	"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
	"$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
	"$t8","$t9",
	"$k0","$k1",
	"$gp", 
	"$sp",
	"$fp",
	"$ra"
};

unsigned int binHash(const char *key) {	
	unsigned int deci = 0, i = 0, value = 0; 
	unsigned int k = atoi(key);

	while (k != 0){
		value = k % 10;
		k /= 10;
		deci += value * pow(2, i); 
		++i;
	}	
	return deci; 
}

int check(char* bits) {
	if (strlen(bits) != LENGTH) {
		return false;
	}
	for (int i = 0; i < LENGTH; i++) {
		if (bits[i] != '0' && bits[i] != '1') {
			return false;
		}
	}
	return true;
}

void ParseInstruction(char *in) {
	int i;
	int n = strlen(in);
	char* ptr = in;

	char *op = malloc(sizeof(char) * 6);
	for (i = 0; i < 6; i++) {
	    op[i] = *ptr;
	    ptr+=1;
	}

	char *rs = malloc(sizeof(char) * 5);
	for (i = 0; i < 5; i++) {
		rs[i] = *ptr;
		ptr+=1;
	}

	char *rt = malloc(sizeof(char) * 5);
	for (i = 0; i < 5; i++) {
		rt[i] = *ptr;
		ptr+=1;
	}
	
	char *rd = malloc(sizeof(char) * 5);
	for (i = 0; i < 5; i++) {
		rd[i] = *ptr;
		ptr+=1;
	}

	char *shamt = malloc(sizeof(char) * 5);
	for (i = 0; i < 5; i++) {
		shamt[i] = *ptr;
		ptr+=1;
	}

	char *funct= malloc(sizeof(char) * 6);
	for (i = 0; i < 6; i++) {
		funct[i] = *ptr;
		ptr+=1;
	}

	char cat[26];
	int *memloc; 
	int hash = binHash(op); 
	int fhash = binHash(funct);
	switch(hash) {
		case 2: 
			memloc = (int*)&regs[31];
			printf("j %p\n", &memloc);
			break;
		case 4:
			strcpy(cat, rd);
			strcat(cat, shamt);
			strcat(cat, funct);
			memloc = (int*)&regs[1];
			printf("beq %s %s %p\n", regs[binHash(rs)], regs[binHash(rt)], &memloc);
			break;
		case 5:
			strcpy(cat, rd);
			strcat(cat, shamt);
			strcat(cat, funct);
			memloc = (int*)&regs[1];
			printf("bne %s %s %p\n", regs[binHash(rs)], regs[binHash(rt)], &memloc);
			break;
		case 8:
			strcpy(cat, rd);
			strcat(cat, shamt);
			strcat(cat, funct);
			printf("addi %s %s %d\n", regs[binHash(rs)], regs[binHash(rt)], binHash(cat));
			break;
		case 35:
			strcpy(cat, rd);
			strcpy(cat, shamt);
			strcat(cat, funct);
			printf("lw %s %d(%s)\n", regs[binHash(rt)], binHash(cat), regs[binHash(rs)]);
			break;
		case 43:
			strcpy(cat, rd);
			strcpy(cat, shamt);
			strcat(cat, funct);
			printf("sw %s %d(%s)\n", regs[binHash(rt)], binHash(cat), regs[binHash(rs)]);
			break;
		case 0:
			switch(fhash){
				case 0:
					printf("sll %s %s %d\n", regs[binHash(rd)], regs[binHash(rt)], binHash(shamt));
					break;
				case 2:
					printf("srl %s %s %d\n", regs[binHash(rd)], regs[binHash(rt)], binHash(shamt));
					break;
				case 8:
					strcpy(cat, rs);
					printf("jr %s\n", regs[binHash(rs)]);
					break;
				case 32:
					printf("add %s %s %s\n", regs[binHash(rd)], regs[binHash(rs)], regs[binHash(rt)]);	
					break;
				case 34:
					printf("sub %s %s %s\n", regs[binHash(rd)], regs[binHash(rs)], regs[binHash(rt)]);
					break;
				case 42:
					printf("slt %s %s %s\n", regs[binHash(rd)], regs[binHash(rs)], regs[binHash(rt)]);		
					break;
			}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "No argument found\n");
		return -1;
	}

	char *in = argv[1];	// 00011000101000010000001010011100	
	
	if (!check(in)) {
		fprintf(stderr, "Invalid bit string\n");
		return -2;
	}

	ParseInstruction(in);
}