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
%type <nb> ArithExpr Expr DivMul Term
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
If: tIf tOP Expr {free_all_temp_addr();} tCP Body;
While: tWhile tOP Expr {free_all_temp_addr();} tCP Body;
BoolCheck: tSup
        | tInf
        | tEQEQ
        | tDiff;
Expr: ArithExpr BoolCheck Expr | ArithExpr;
ArithExpr: ArithExpr tAdd DivMul {
		free_all_temp_addr();
     	int temp = use_temp_addr();
     	add_asm_3(ADD, temp, $1, $3);
     	$$ = temp;
	}
     | ArithExpr tSub DivMul {
     	free_all_temp_addr();
     	int temp = use_temp_addr();
     	add_asm_3(SOU, temp, $1, $3);
     	$$ = temp;
     }
     | ArithExpr tAnd DivMul {
     	free_all_temp_addr();
     	int temp = use_temp_addr();
     	add_asm_3(AND, temp, $1, $3);
     	$$ = temp;
     }
     | ArithExpr tOr DivMul {
     	free_all_temp_addr();
     	int temp = use_temp_addr();
     	add_asm_3(OR, temp, $1, $3);
     	$$ = temp;
     }
     | DivMul { $$ = $1; };
DivMul: DivMul tMul Term {
			free_all_temp_addr();
        	int temp = use_temp_addr();
        	add_asm_3(MUL, temp, $1, $3);
        	$$ = temp;	
		}
        | DivMul tDiv Term {
        	free_all_temp_addr();
        	int temp = use_temp_addr();
        	add_asm_3(DIV, temp, $1, $3);
        	$$ = temp;
        }
        | Term { $$ = $1; };
Term: tOP Expr tCP { $$ = $2; }
    | tValInt {
    	int temp = use_temp_addr();
    	add_asm_2(AFC, temp, $1);
    	$$ = temp;
    }
    | tId { $$ = get_symb_addr($1); };
Declaration: tInt tId tSC {
		if(exists_symb($2, IN_CURRENT_SCOPE)) {
			fprintf(stderr, "The variable \"%s\" has already been declared\n", $2);
			return 1;
		} else {
			push_symb($2);
		}};
Affectation: tInt tId tEQ Expr {free_all_temp_addr();} tSC {
		if(exists_symb($2, IN_CURRENT_SCOPE)) {
			fprintf(stderr, "The variable \"%s\" has already been declared\n", $2);
			return 1;
		} else {
			push_symb($2);
		}};
	| tId tEQ Expr {free_all_temp_addr();} tSC {
		if(!exists_symb($1, IN_ANY_SCOPE)) {
			fprintf(stderr, "Unknown variable \"%s\"\n", $1);
			return 1;
		}};
Print: tPrintf tOP Expr {free_all_temp_addr();} tCP tSC {
			add_asm_1(PRI, $3);
		};
Return: tReturn Expr {free_all_temp_addr();} tSC;
%%
int main(void) {
  // yydebug=1;
  int out = yyparse();
  return out;
}
