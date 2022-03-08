%{
#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
int l = 1;
%}
D [0-9]
L [a-zA-Z]
%%
[ \t]+ ;
[\n] {l++;};
"main" { printf("main\n"); return tMain;}
"{" {printf("{\n"); return tOCB;}
"}" {printf("}\n"); return tCCB;}
"const" return tConst;
"int" {printf("int\n"); return tInt;}
"+" return tAdd;
"-" return tSub;
"*" return tMul;
"/" return tDiv;
"<" return tInf;
">" return tSup;
"==" return tEQEQ;
"!=" return tDiff;
"and" return tAnd;
"or" return tOr;
"=" return tEQ;
"(" { printf("(\n"); return tOP;}
")" { printf(")\n"); return tCP;}
"," return tCom;
";" return tSC;
"if" return tIf;
"while" return tWhile;
"return" return tReturn;
"printf" return tPrintf;
{D}+(e{D}+)? { yylval.nb = (int) strtold(yytext, NULL); return tValInt; }	
{L}({L}|{D}|\_)* { return tId; };
. return tError;
%%
int yywrap()
{
return 1 ;
}
void yyerror(char *s) { fprintf(stderr, "%s on line %d\n", s, l); }
