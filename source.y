%{
#include <stdlib.h>
#include <stdio.h>
int var[26];
void yyerror(char *s);
typedef struct Symbol {
    char* name;
    char* type;
    int addr;
} Symbol;
Symbol symb_table[200];
%}
%union { int nb; char var; }
%token tMain tOCB tCCB tConst tInt tAdd tSub tMul tDiv tEQEQ tEQ tOP tCP tCom tSC tIf tWhile tReturn tPrintf tError
%token <nb> tValInt
%token <var> tId
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
If: tIf Cond Body;
While: tWhile Cond Body;
Cond: tOP Expr tCP;
Expr: Expr tAdd DivMul
     | Expr tSub DivMul
     | DivMul;
DivMul: DivMul tMul Term
        | DivMul tDiv Term
        | Term;
Term: tOP Expr tCP
    | tValInt
    | tId;
Ope: tAdd
    | tSub
    | tMul
    | tDiv
    | tEQEQ ;
Declaration: tInt tId tSC;
Affectation: tInt tId tEQ tValInt tSC
            | tId tEQ tValInt tSC
            | tId tEQ tId tSC;
Print: tPrintf tOP Printable tCP tSC;
Printable: tValInt
            | tId;
Return: tReturn Returnable tSC;
Returnable: tValInt
            | tId;
%%
void yyerror(char *s) { fprintf(stderr, "%s\n", s); }
int main(void) {
  printf("Compiler\n"); // yydebug=1;
  yyparse();
  return 0;
}
