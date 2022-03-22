#include <stdio.h>
#include <stdlib.h>
#include "asm_table.h"
#define MEM_MAX_INST 1024

int mem_table[MEM_MAX_INST];
int i = 0;

int main(int argc, char **argv)
{
    while (i < MEM_MAX_INST)
    {
        switch (asm_table[i].operator)
        {
        case 0:
            ADD(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        case 1:
            MUL(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        case 2:
            SOU(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        case 3:
            DIV(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        case 4:
            COP(asm_table[i].op1, asm_table[i].op2);
            i++;
        case 5:
            AFC(asm_table[i].op1, asm_table[i].op2);
            i++;
        case 6:
            JMP(asm_table[i].op1);
        case 7:
            JMF(asm_table[i].op1, asm_table[i].op2);
        case 8:
            INF(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        case 9:
            SUP(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        case 10:
            EQU(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        case 11:
            PRI(asm_table[i].op1);
            i++;
        case 12:
            AND(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        case 13:
            OR(asm_table[i].op1, asm_table[i].op2, asm_table[i].op3);
            i++;
        }
    }
}

void ADD(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] + mem_table[op3];
}

void MUL(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] * mem_table[op3];
}

void SOU(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] - mem_table[op3];
}

void DIV(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] / mem_table[op3];
}

void COP(int op1, int op2)
{
    mem_table[op1] = mem_table[op2];
}

void AFC(int op1, int op2)
{
    mem_table[op1] = op2;
}

void JMP(int op1)
{
    i = op1;
}

void JMF(int op1, int op2)
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

void INF(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] < mem_table[op3];
}

void SUP(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] > mem_table[op3];
}

void EQU(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] == mem_table[op3];
}

void PRI(int op1, int op2, int op3)
{
    printf(mem_table[op1]);
}

void AND(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] && mem_table[op3];
}

void OR(int op1, int op2, int op3)
{
    mem_table[op1] = mem_table[op2] || mem_table[op3];
}