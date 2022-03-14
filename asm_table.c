#include <stdio.h>
#include "asm_table.h"
#define MAX_ASM_INST 1024

AsmInst asm_table[MAX_ASM_INST];
int index = 0;

void add_asm_2(char* operator, char* op1, char* op2) {
	AsmInst inst = {operator, op1, op2};
	asm_table[index] = inst;
	index++;
}

void add_asm_3(char* operator, char* op1, char* op2, char* op3) {
	AsmInst inst = {operator, op1, op2, op3};
	asm_table[index] = inst;
	index++;
}

void print_asm_table() {
	int i = 0;
	
	while(i < MAX_ASM_INST && asm_table[i].operator != NULL) {
		print_asm_inst(asm_table[i]);
		i++;
	}
}
void print_asm_inst(AsmInst inst) {
	printf("{ operator = %s, op1 = %s, op2 = %s, op3 = %s }\n", inst.operator, inst.op1, inst.op2, inst.op3);
}
