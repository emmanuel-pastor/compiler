#include <stdio.h>
#include "asm_table.h"
#define MAX_ASM_INST 1024
int index = 0;
AsmInst asm_table[MAX_ASM_INST];
void add_asm_1(Operator operator, int op1) {
	AsmInst inst = {operator, op1};
	asm_table[index] = inst;
	index++;
}

void add_asm_2(Operator operator, int op1, int op2) {
	AsmInst inst = {operator, op1, op2};
	asm_table[index] = inst;
	index++;
}

void add_asm_3(Operator operator, int op1, int op2, int op3) {
	AsmInst inst = {operator, op1, op2, op3};
	asm_table[index] = inst;
	index++;
}

void update_last_if_inst() {
	int i = index;
	int found = 0;
	while(!found && i >= 0) {
		AsmInst inst = asm_table[i];
		if(inst.operator == JMF) {
			found = 1;
			asm_table[i] = (AsmInst) {inst.operator, inst.op1, index};
		}
		i--;
	}
}

int get_nb_inst() {
	return index;
}

void print_asm_table() {
	int i = 0;
	
	while(i < MAX_ASM_INST && i < index) {
		printf("%d: ", i);
		print_asm_inst(asm_table[i]);
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
	return str;
}
void print_asm_inst(AsmInst inst) {
	printf("{operator = %s, op1 = %d, op2 = %d, op3 = %d}\n", asm_ope_to_string(inst.operator), inst.op1, inst.op2, inst.op3);
}
