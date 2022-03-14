#ifndef ASM_TABLE_H
#define ASM_TABLE_H

typedef enum Operator {ADD, MUL, SOU, DIV, COP, AFC, JMP, JMF, INF, SUP, EQU, PRI} Operator;

typedef struct AsmInst {
    Operator operator;
    char* op1;
    char* op2;
    char* op3;
} AsmInst;

void add_asm_2(Operator operator, char* op1, char* op2);
void add_asm_3(Operator operator, char* op1, char* op2, char* op3);
void print_asm_table();
char* asm_ope_to_string(Operator operator);
void print_asm_inst(AsmInst inst);
#endif
