%{
#include <stdlib.h>
#include <stdio.h>
int var[26];
void yyerror(char *s);
typedef struct Symbol {
    char* name;
    char* type;
    int addr;
    int scope;
} Symbol;
Symbol symb_table[200];
typedef struct AsmInst {
    char* operator;
    char* op1;
    char* op2;
    char* op3;
} AsmInst;
AsmInst asm_table[1024];
%}
%union { int nb; char var; }
%token tMain tOCB tCCB tConst tInt tAdd tSub tMul tDiv tInf tSup tEQEQ tEQ tOP tCP tCom tSC tIf tWhile tReturn tPrintf tError
%token <nb> tValInt
%token <var> tId
%type <nb> Expr DivMul Term
%start Compiler
%%
Compiler: tInt tMain tOP tCP Body;
Body: tOCB Instructions tCCB;
Instructions: Inst Instructions | ;
Inst: If
    | While
    | Declaration
    | Affectation
    | Print
    | Return;
If: tIf tOP Expr tCP Body;
While: tWhile tOP Expr tCP Body;
BoolOpe: tSup
        | tInf
        | tEQEQ;
Expr: Expr tAdd DivMul
     | Expr tSub DivMul
     | Expr BoolOpe DivMul
     | DivMul;
DivMul: DivMul tMul Term
        | DivMul tDiv Term
        | Term;
Term: tOP Expr tCP
    | tValInt
    | tId;
Declaration: tInt tId tSC;
Affectation: tInt tId tEQ tValInt tSC
            | tId tEQ tValInt tSC
            | tId tEQ tId tSC;
Print: tPrintf tOP Expr tCP tSC;
Return: tReturn Expr tSC;
%%
void yyerror(char *s) { fprintf(stderr, "%s\n", s); }
int main(void) {
  printf("Compiler\n"); // yydebug=1;
  yyparse();
  return 0;
}
