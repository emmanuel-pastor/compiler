#ifndef ASM_TABLE_H
#define ASM_TABLE_H

typedef struct AsmInst {
    char* operator;
    char* op1;
    char* op2;
    char* op3;
} AsmInst;

void add_asm_2(char* operator, char* op1, char* op2);
void add_asm_3(char* operator, char* op1, char* op2, char* op3);
void print_asm_table();
void print_asm_inst(AsmInst inst);
#endif
