#include <stdio.h>
#include <stdlib.h>
#include "asm_table.h"
#define MAX_ASM_INST 256
int index = 0;
extern AsmInst asm_table[MAX_ASM_INST];
int start_inst_nb = 0;

void checkInstructionMemory() {
    if(index >= MAX_ASM_INST) {
        fprintf(stderr, "The instruction memory is full (more than %d instructions)\n", MAX_ASM_INST);
        exit(EXIT_FAILURE);
    }
}

void add_asm_1(Operator operator, int op1) {
    checkInstructionMemory();
	AsmInst inst = {operator, op1};
	asm_table[index] = inst;
	index++;
}

void add_asm_2(Operator operator, int op1, int op2) {
    checkInstructionMemory();
	AsmInst inst = {operator, op1, op2};
	asm_table[index] = inst;
	index++;
}

void add_asm_3(Operator operator, int op1, int op2, int op3) {
    checkInstructionMemory();
	AsmInst inst = {operator, op1, op2, op3};
	asm_table[index] = inst;
	index++;
}

int get_inst_nb() {
	return index;
}

void update_jmf(int inst_to_modify, int new_value) {
	AsmInst inst = asm_table[inst_to_modify];
	asm_table[inst_to_modify] = (AsmInst) {inst.operator, inst.op1, new_value};
}

void update_jmp(int inst_to_modify, int new_value) {
	AsmInst inst = asm_table[inst_to_modify];
	asm_table[inst_to_modify] = (AsmInst) {inst.operator, new_value};
}

void print_asm_table(FILE* output) {
	int i = 0;
	
	while(i < MAX_ASM_INST && i < index) {
		fprintf(output, "%d: ", i);
		print_asm_inst(output, asm_table[i]);
		i++;
	}
}
char* asm_ope_to_string(Operator operator) {
	char* str;
	switch(operator) {
		case 0: str = "ADD"; break;
		case 1: str = "MUL"; break;
		case 2: str = "SOU"; break;
		case 3: str = "DIV"; break;
		case 4: str = "COP"; break;
		case 5: str = "AFC"; break;
		case 6: str = "JMP"; break;
		case 7: str = "JMF"; break;
		case 8: str = "INF"; break;
		case 9: str = "SUP"; break;
		case 10: str = "EQU"; break;
		case 11: str = "PRI"; break;
		case 12: str = "AND"; break;
		case 13: str = "OR"; break;
	}
}
void print_asm_inst(FILE* output, AsmInst inst) {
	fprintf(output, "%s %d %d %d\n", asm_ope_to_string(inst.operator), inst.op1, inst.op2, inst.op3);
}
