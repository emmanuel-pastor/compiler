#ifndef ASM_TABLE_H
#define ASM_TABLE_H

typedef enum Operator {ADD, MUL, SOU, DIV, COP, AFC, JMP, JMF, INF, SUP, EQU, PRI, AND, OR} Operator;

typedef struct AsmInst {
    Operator operator;
    int op1;
    int op2;
    int op3;
} AsmInst;
void add_asm_1(Operator operator, int op1);
void add_asm_2(Operator operator, int op1, int op2);
void add_asm_3(Operator operator, int op1, int op2, int op3);
int get_inst_nb();
void update_jmf(int inst_to_modify, int new_value);
void print_asm_table();
char* asm_ope_to_string(Operator operator);
void print_asm_inst(AsmInst inst);
#endif
