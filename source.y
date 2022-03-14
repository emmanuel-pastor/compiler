%{
#include <stdlib.h>
#include <stdio.h>
#include "symb_table.h"
#include "asm_table.h"
#define IN_CURRENT_SCOPE 0
#define IN_ANY_SCOPE 1

void yyerror(char *s);
%}
%union { int nb; char* var; }
%token tMain tOCB tCCB tConst tInt tAdd tSub tMul tDiv tInf tSup tEQEQ tDiff tAnd tOr tEQ tOP tCP tComma tSC tIf tWhile tReturn tCom tPrintf tError
%token <nb> tValInt
%token <var> tId
%type <nb> ArithExpr DivMul Term
%start Compiler
%%
Compiler: tInt tMain tOP tCP Body;
Body: tOCB Instructions tCCB {decr_scope();};
Instructions: Inst Instructions
	| ;
Inst: If
    | While
    | Declaration
    | Affectation
    | Print
    | Return
    | tCom;
If: tIf tOP Expr tCP Body;
While: tWhile tOP Expr tCP Body;
BoolCheck: tSup
        | tInf
        | tEQEQ
        | tDiff;
BoolOpe: tAnd
	| tOr;
Expr: ArithExpr BoolCheck Expr | ArithExpr;
ArithExpr: ArithExpr tAdd DivMul
     | ArithExpr tSub DivMul
     | ArithExpr BoolOpe DivMul
     | DivMul;
DivMul: DivMul tMul Term
        | DivMul tDiv Term
        | Term;
Term: tOP Expr tCP
    | tValInt
    | tId;
Declaration: tInt tId tSC {
		if(exists_symb($2, IN_CURRENT_SCOPE)) {
			fprintf(stderr, "The variable \"%s\" has already been declared\n", $2);
			return 1;
		} else {
			push_symb($2);
		}};
Affectation: tInt tId tEQ Expr tSC {
		if(exists_symb($2, IN_CURRENT_SCOPE)) {
			fprintf(stderr, "The variable \"%s\" has already been declared\n", $2);
			return 1;
		} else {
			push_symb($2);
		}};
	| tId tEQ Expr tSC {
		if(!exists_symb($1, IN_ANY_SCOPE)) {
			fprintf(stderr, "Unknown variable \"%s\"\n", $1);
			return 1;
		}};
Print: tPrintf tOP Expr tCP tSC;
Return: tReturn Expr tSC;
%%
int main(void) {
  // yydebug=1;
  int out = yyparse();
  print_asm_table();
  return out;
}
