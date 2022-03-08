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
"main" return tMain;
"{" return tOCB;
"}" return tCCB;
"const" return tConst;
"int" return tInt;
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
"(" return tOP;
")" return tCP;
"," return tComma;
";" return tSC;
"if" return tIf;
"while" return tWhile;
"return" return tReturn;
"printf" return tPrintf;
[\/]{2}.* return tCom;
{D}+(e{D}+)? { yylval.nb = (int) strtold(yytext, NULL); return tValInt; }	
{L}({L}|{D}|\_)* return tId;
. return tError;
%%
int yywrap()
{
return 1 ;
}
int yyerror(char *s) { fprintf(stderr, "%s on line %d near %s\n", s, l, yytext);}
