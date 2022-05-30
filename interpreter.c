#include <stdio.h>
#include <stdlib.h>
#include "asm_table.h"
#define MAX_ASM_INST 1024
#define MAX_MEM 220

int mem_table[MAX_MEM];
AsmInst asm_table[MAX_ASM_INST];
int i = 0;

void add(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] + mem_table[op3];
}

void mul(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] * mem_table[op3];
}

void sou(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] - mem_table[op3];
}

void div_asm(int op1, int op2, int op3)
{
    mem_table[op1] = (int) (mem_table[op2] / mem_table[op3]);
}

void cop(int op1, int op2)
{
    mem_table[op1] = mem_table[op2];
}

void afc(int op1, int op2)
{
    mem_table[op1] = op2;
}

void jmp(int op1)
{
    i = op1;
}

void jmf(int op1, int op2)
{
    if (!mem_table[op1])
    {
        i = op2;
    }
    else
    {
        i++;
    }
}

void inf(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] < mem_table[op3];
}

void sup(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] > mem_table[op3];
}

void equ(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] == mem_table[op3];
}

void pri(int op1)
{
    printf("%d\n", mem_table[op1]);
}

void and(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] && mem_table[op3];
}

void or(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] || mem_table[op3];
}

void launch_interpreter(int nb_inst)
{
    while (i < nb_inst)
    {
        switch (asm_table[i].operator)
        {
        case 0:
            add(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        case 1:
            mul(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        case 2:
            sou(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        case 3:
            div_asm(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        case 4:
            cop(asm_table[i].op1, asm_table[i].op2);
            i++;
            break;
        case 5:
            afc(asm_table[i].op1, asm_table[i].op2);
            i++;
            break;
        case 6:
            jmp(asm_table[i].op1);
            break;
        case 7:
            jmf(asm_table[i].op1, asm_table[i].op2);
            break;
        case 8:
            inf(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        case 9:
            sup(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        case 10:
            equ(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        case 11:
            pri(asm_table[i].op1);
            i++;
            break;
        case 12:
            and(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        case 13:
            or(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
            break;
        }
    }
}
