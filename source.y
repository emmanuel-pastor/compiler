%{
#include <stdlib.h>
#include <stdio.h>
#include "symb_table.h"
#include "asm_table.h"
#include "jmp_table.h"
#include "interpreter.h"
#define IN_CURRENT_SCOPE 0
#define IN_ANY_SCOPE 1

int line = 1;
void yyerror(char *s);
int start_inst = 0;
%}
%union { int nb; char* var; }
%token tMain tOCB tCCB tConst tInt tAdd tSub tMul tDiv tInf tSup tEQEQ tDiff tAnd tOr tEQ tOP tCP tComma tSC tIf tElse tWhile tReturn tCom tPrintf tError
%token <nb> tValInt
%token <var> tId
%type <nb> ArithExpr BoolExpr Expr DivMul Term
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
If: tIf tOP Expr {free_all_temp_addr();} tCP {push_if_start(get_inst_nb()); add_asm_2(JMF, $3, -1);} Body Else;
Else: tElse {push_else_start(get_inst_nb()); add_asm_1(JMP, -1); update_jmf(pop_if_start(), get_inst_nb());} Body {update_jmp(pop_else_start(), get_inst_nb());}
	| {update_jmf(pop_if_start(), get_inst_nb());};
While: tWhile tOP {push_while_start(get_inst_nb()); push_if_start(get_inst_nb());} Expr {free_all_temp_addr();} tCP {push_if_start(get_inst_nb()); add_asm_2(JMF, $4, -1);} Body {add_asm_1(JMP, pop_while_start()); update_jmf(pop_if_start(), get_inst_nb());};
Expr: BoolExpr tAnd Expr {
     	free_temp_addr($1);
     	int temp = use_temp_addr();
     	add_asm_3(AND, temp, $1, $3);
        if($3 != temp) free_temp_addr($3);
     	$$ = temp;
     }
     | BoolExpr tOr Expr {
     	free_temp_addr($1);
     	int temp = use_temp_addr();
     	add_asm_3(OR, temp, $1, $3);
        if($3 != temp) free_temp_addr($3);
     	$$ = temp;
     }
	| BoolExpr { $$ = $1; };
BoolExpr: ArithExpr tSup ArithExpr {
     	free_temp_addr($1);
     	int temp = use_temp_addr();
		add_asm_3(SUP, temp, $1, $3);
        if($3 != temp) free_temp_addr($3);
		$$ = temp;
	}
	| ArithExpr tInf ArithExpr {
     	free_temp_addr($1);
     	int temp = use_temp_addr();
		add_asm_3(INF, temp, $1, $3);
        if($3 != temp) free_temp_addr($3);
		$$ = temp;
	}
	| ArithExpr tEQEQ ArithExpr {
		free_temp_addr($1);
     	int temp = use_temp_addr();
		add_asm_3(EQU, temp, $1, $3);
        if($3 != temp) free_temp_addr($3);
		$$ = temp;
	}
	| ArithExpr tDiff ArithExpr
	| ArithExpr { $$ = $1; } ;
ArithExpr: ArithExpr tAdd DivMul {
     	free_temp_addr($1);
     	int temp = use_temp_addr();
     	add_asm_3(ADD, temp, $1, $3);
        if($3 != temp) free_temp_addr($3);
     	$$ = temp;
	}
     | ArithExpr tSub DivMul {
    	free_temp_addr($1);
     	int temp = use_temp_addr();
     	add_asm_3(SOU, temp, $1, $3);
        if($3 != temp) free_temp_addr($3);
     	$$ = temp;
     }
     | DivMul { $$ = $1; };
DivMul: DivMul tMul Term {
 		free_temp_addr($1);
 		int temp = use_temp_addr();
    	add_asm_3(MUL, temp, $1, $3);
    	if($3 != temp) free_temp_addr($3);
    	$$ = temp;	
	}
    | DivMul tDiv Term {
    	free_temp_addr($1);
     	int temp = use_temp_addr();
    	add_asm_3(DIV, temp, $1, $3);
    	if($3 != temp) free_temp_addr($3);
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
			fprintf(stderr, "The variable \"%s\" on line %d has already been declared\n", $2, line);
			return 1;
		} else {
			push_symb($2);
		}};
Affectation: tInt tId tEQ Expr {free_all_temp_addr();} tSC {
		if(exists_symb($2, IN_CURRENT_SCOPE)) {
			fprintf(stderr, "The variable \"%s\" on line %d has already been declared\n", $2, line);
			return 1;
		} else {
			int addr = push_symb($2);
			add_asm_2(COP, addr, $4);
		}};
	| tId tEQ Expr {free_all_temp_addr();} tSC {
		if(!exists_symb($1, IN_ANY_SCOPE)) {
			fprintf(stderr, "Unknown variable \"%s\" on line %d\n", $1, line);
			return 1;
		} else {
			add_asm_2(COP, get_symb_addr($1), $3);
		}};
Print: tPrintf tOP Expr {free_all_temp_addr();} tCP tSC {
			add_asm_1(PRI, $3);
		};
Return: tReturn Expr {free_all_temp_addr();} tSC;
%%
int main(void) {
  // yydebug=1;
  int out = yyparse();
  //print_asm_table();
  //launch_interpreter(get_inst_nb());
  return out;
}
